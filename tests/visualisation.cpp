#include <systemc.h>

int sc_main (int argc, char * argv[])
{
    if(argc != 2)
    {
        printf("Usage ./visualisation N\n");
        return 1;
    }
    int n = atoi(argv[1]);
   // Un pointeur sur l'objet qui permet de gérer les traces
   sc_trace_file *trace_f;

   // Cette fonction crée l'objet
   // L'argument est le nom du fichier qui sera créé.
   // L'extension .vcd est ajoutée automatiquement
   trace_f = sc_create_vcd_trace_file ("my_simu_trace");
   // On peut aussi préciser l'unité de temps dans le fichier vcd
   trace_f->set_time_unit(1, SC_NS);

   int val = 0;

   // Ajoute la variable t aux éléments à tracer
   // Les arguments de la fonction sont:
   //    - le pointeur vers le fichier de trace
   //    - la variable/objet à tracer
   //    - le nom dans dans le fichier généré
   sc_trace(trace_f, val, "t");

   // La simulation
    for(int i = 0; i < n; i++)
    {
        val++;
        cout << "idx: " << val << endl;
        sc_start(10, SC_NS);
    }
   // Ferme le fichier de trace
   // ne peut êter fait qu'à la fin de la simulation
   sc_close_vcd_trace_file(trace_f);

   return 0;
}
