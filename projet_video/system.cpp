/**********************************************************************
 * File : system.cpp
 * Date : 2008-2016
 * Author :  Alexis Polti/Tarik Graba
 *
 * This program is released under the GNU public license
 * Télécom ParisTECH
 *
 * Testbench pour video_in
 **********************************************************************/

#include <systemc.h>
#include <sstream>
#include "video_in.h"
#include "convol.h"
#include "zoom.h"
#include "filter.h"
#include "video_out.h"

/***************************************************
 *	MAIN
 **************************************************/

int sc_main (int argc, char *argv[])
{
    int	ncycles;
    int nb_filters = argc - 2;

    if (argc >= 2) {
        std::stringstream arg1(argv[1]);
        arg1 >> ncycles;
    } else {
        cout << "Le nombre de cycles de simulation doit être passé en argument (-1 pour une simulation illimitée)" << endl
             << "Les filtres a appliquer peuvent être passés en argument (ex: mean, sobel)" << endl;
        exit(1);
    }

    /******************************************************
     *      Déclaration des signaux
     *****************************************************/

    /* La période de l'horloge du signal vidéo */
    sc_time pix_period(74, SC_NS);

    sc_clock                        signal_clk("Clock", pix_period);
    sc_signal<bool>                 signal_resetn;

    /********************************************************
     *	Instanciation des modules
     *******************************************************/

    VIDEO_IN video_in("VIDEO_GEN");
    FILTER * filter[nb_filters];
    for(int i = 0; i < nb_filters; i++){
        std::string filtername = argv[i + 2];
        if(!filtername.compare("zoom"))
            filter[i] = new ZOOM("VIDEO_ZOOM");
        else
            filter[i] = new CONVOL("VIDEO_CONVOL", filtername);
    }
    VIDEO_OUT video_out("VIDEO_OUT");

    /*********************************************************
     *	Connexion des composants
     ********************************************************/

    video_in.clk        (signal_clk);
    video_in.reset_n    (signal_resetn);
    video_out.clk       (signal_clk);
    video_out.reset_n   (signal_resetn);

    sc_signal<bool>             signal_vref[nb_filters + 1];
    sc_signal<bool>             signal_href[nb_filters + 1];
    sc_signal<unsigned char>    signal_pixel[nb_filters + 1];

    video_in.href        (signal_href [0]);
    video_in.vref        (signal_vref [0]);
    video_in.pixel_out   (signal_pixel[0]);
    for(int i = 0; i < nb_filters; i++)
    {
        filter[i]->clk     (signal_clk);
        filter[i]->reset_n (signal_resetn);
        filter[i]->h_in    (signal_href [i]);
        filter[i]->v_in    (signal_vref [i]);
        filter[i]->p_in    (signal_pixel[i]);
        filter[i]->v_out   (signal_vref [i+1]);
        filter[i]->h_out   (signal_href [i+1]);
        filter[i]->p_out   (signal_pixel[i+1]);
    }
    video_out.href       (signal_href [nb_filters]);
    video_out.vref       (signal_vref [nb_filters]);
    video_out.pixel_in   (signal_pixel[nb_filters]);

    /*********************************************************
     *	Traces
     ********************************************************/

    /* fichier de traces */
    sc_trace_file * my_trace_file;
    my_trace_file = sc_create_vcd_trace_file ("simulation_trace");
    my_trace_file->set_time_unit(1,SC_NS);

#define TRACE(x) sc_trace(my_trace_file, x, #x)

    /* chronogrammes signaux CLK et NRESET */
    TRACE(signal_clk);
    TRACE(signal_resetn);

    /* chronogrammes video */
    /*
    TRACE(signal_href [0]);
    TRACE(signal_vref [0]);
    TRACE(signal_pixel[0]);
    TRACE(signal_href [nb_filters]);
    TRACE(signal_vref [nb_filters]);
    TRACE(signal_pixel[nb_filters]);
    */

#undef TRACE

    /*********************************************************
     *	Simulation
     ********************************************************/

    /* Initialisation de la simulation */
    sc_start(SC_ZERO_TIME);
    signal_resetn = true;
    sc_start(10*signal_clk.period());

    /* Génération d'un reset */
    signal_resetn = false;
    sc_start(10*signal_clk.period());
    signal_resetn = true;

    /* Lancement de la simulation */
    if(ncycles >= 0) {
       cout << "Simulation lancée pour " << ncycles << " cycle de " << signal_clk.period() << endl;
       sc_start(ncycles * signal_clk.period());
    } else {
       cout << "Simulation lancée en continu (CTRL-C pour l'arrêter)" << endl;
       sc_start();
    }

    cout << "Fin de la simulation @ " << sc_time_stamp() << endl;

    /* Close trace file */
    sc_close_vcd_trace_file (my_trace_file);

    return EXIT_SUCCESS;
}
