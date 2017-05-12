#include <systemc.h>

struct Pixel
{
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
void sc_trace(sc_trace_file* _f, const Pixel& _foo, const std::string& _s)
{
   sc_trace(_f, _foo.r, _s + "_r");
   sc_trace(_f, _foo.g, _s + "_g");
   sc_trace(_f, _foo.b, _s + "_b");
}

SC_MODULE(sum)
{
   sc_in<Pixel> p1;
   sc_in<Pixel> p2;
   sc_out<Pixel> pSum;
   // Le constructeur du module
   SC_CTOR(sum):p1("p1"),p2("p2"),pSum("pSum")
   {
      SC_METHOD(compute_sum);
      sensitive << p1 << p2;
   }

   void compute_sum()
   {
     Pixel pSum_;
     Pixel p1_ = p1;
     Pixel p2_ = p2;
     pSum_.r = p1_.r + p2_.r;
     pSum_.g = p1_.g + p2_.g;
     pSum_.b = p1_.b + p2_.b;
     pSum = pSum_;
   }
};

int sc_main (int argc, char * argv[])
{
    sc_trace_file *trace_f;
    trace_f = sc_create_vcd_trace_file ("my_simu_trace");
    trace_f->set_time_unit(1, SC_NS);

    Pixel p;
    // init des pixels 1, 2 et sum
    sc_signal<Pixel> sig_p1;
    sc_trace(trace_f, sig_p1, "pixel_1");
    sc_signal<Pixel> sig_p2;
    sc_trace(trace_f, sig_p2, "pixel_2");
    sc_signal<Pixel> sig_pSum;
    sc_trace(trace_f, sig_pSum, "pixel_sum");
    // creation du module de somme
    sum sum_i("sum");
    sum_i.p1(sig_p1);
    sum_i.p2(sig_p2);
    sum_i.pSum(sig_pSum);

    sig_p1 = p;
    sig_p2 = p;
    sc_start(5, SC_NS);
    p.r = 1;
    p.g = 2;
    p.b = 3;
    sig_p1 = p;
    sc_start(5, SC_NS);
    p.r = 9;
    p.g = 8;
    p.b = 7;
    sig_p2 = p;
    sc_start(5, SC_NS);

    sc_close_vcd_trace_file(trace_f);
    return 0;
}