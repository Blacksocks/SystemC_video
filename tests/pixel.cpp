#include <systemc.h>

struct Pixel {
    sc_uint<5> r;
    sc_uint<6> g;
    sc_uint<5> b;
    // un constructeur particulier avec des valeurs par défaut
    Pixel(int _r=0, int _g=0, int _b=0): r(_r), g(_g), b(_b) { }

    bool operator == (const Pixel &other) {
        return (r == other.r) && (g == other.g) && (b == other.b);
    }
    // On doit pouvoir imprimer la valeur d'un objet de ce type
    // l'opérateur << est un opérateur de la classe std::ostream
    friend ostream& operator << (ostream& o, const Pixel& P) {
        o << "{" << P.r << "," << P.g << "," << P.b << "}";
        return o;
    }
};

// surcharge de la fonction sc_trace pour le type pixel
void sc_trace( sc_trace_file* _f, const Pixel& _foo, const std::string& _s ) {
   sc_trace( _f, _foo.r, _s + "_r" );
   sc_trace( _f, _foo.g, _s + "_g" );
   sc_trace( _f, _foo.b, _s + "_b" );
}

int sc_main (int argc, char * argv[])
{
    sc_trace_file *trace_f;
    trace_f = sc_create_vcd_trace_file ("my_simu_trace");
    trace_f->set_time_unit(1, SC_NS);

    Pixel p;
    sc_trace(trace_f, p, "pixel");
    sc_signal<Pixel> signal;
    signal = p;

    for(unsigned int i = 0; i < 256; i++)
    {
        // red
        p = signal;
        if(p.r < (i * 32 / 256))
            p.r++;
        signal = p;
        sc_start(10, SC_NS);
        // green
        p = signal;
        if(p.g < (i * 64 / 256))
            p.g++;
        signal = p;
        sc_start(10, SC_NS);
        // blue
        p = signal;
        if(p.b < (i * 32 / 256))
            p.b++;
        signal = p;
        sc_start(10, SC_NS);
    }

    sc_close_vcd_trace_file(trace_f);
    return 0;
}
