#include <systemc.h>

// Calculate greatest common divisor between x and y
unsigned int pgcd_compute(unsigned int x, unsigned int y)
{
    int min = (x < y) ? x : y;
    int max = (x < y) ? y : x;
    if(max == min)
        return min;
    return pgcd_compute(min, max - min);
}

// Calculate greatest common divisor between a and b
SC_MODULE(mod_pgcd)
{
    sc_in<bool> clk;
    sc_in<bool> valid;
    sc_in<sc_uint<8> > a;
    sc_in<sc_uint<8> > b;

    sc_out<bool> ready;
    sc_out<sc_uint<8> > pgcd;

    SC_CTOR(mod_pgcd):clk("clk"),valid("valid"),a("a"),b("b"),ready("ready"),pgcd("pgcd")
    {
        SC_CTHREAD(compute_pgcd, clk);
    }

    void compute_pgcd()
    {
        while(1)
        {
            wait();
            ready = false;
            if(!valid)
                continue;
            wait(1);
            sc_uint<8> a_ = a;
            sc_uint<8> b_ = b;
            pgcd = pgcd_compute(a_.to_uint(), b_.to_uint());
            ready = true;
        }
    }
};

// Calculate greatest common divisor using methods
SC_MODULE(mod_pgcd_rtl)
{
    sc_in<bool> clk;
    sc_in<bool> valid;
    sc_in<sc_uint<8> > a;
    sc_in<sc_uint<8> > b;

    sc_out<bool> ready;
    sc_out<sc_uint<8> > pgcd;

    sc_signal<sc_uint<8> > min;
    sc_signal<sc_uint<8> > max;

    // is calculating launched ?
    bool state;

    SC_CTOR(mod_pgcd_rtl):clk("clk"),valid("valid"),a("a"),b("b"),ready("ready"),pgcd("pgcd")
    {
        state = false;
        SC_METHOD(compute_minmax);
        sensitive << clk.pos() << valid.pos();
    }

    void compute_minmax()
    {
        ready = false;
        if(!state)
        {
            if(!valid)
                return;
            min = (a < b) ? a : b;
            max = (a < b) ? b : a;
            state = true;
            return;
        }
        sc_uint<8> max_ = max;
        sc_uint<8> min_ = min;
        pgcd = max_;
        if(min_ == max_)
        {
            ready = true;
            state = false;
            return;
        }
        max_ = max_ - min_;
        min = (max_ < min_) ? max_ : min_;
        max = (max_ < min_) ? min_ : max_;
    }
};

int sc_main(int argc, char * argv[])
{
    sc_trace_file * trace_f;
    trace_f = sc_create_vcd_trace_file("my_simu_trace");
    trace_f->set_time_unit(1, SC_NS);

    // init clock
    sc_clock clk("clk", 2, SC_NS);
    sc_trace(trace_f, clk, "clk");
    // init valid and ready signals
    sc_signal<bool> sig_valid;
    sc_trace(trace_f, sig_valid, "valid");
    sc_signal<bool> sig_ready;
    sc_trace(trace_f, sig_ready, "ready");
    // init data signals
    sc_signal<sc_uint<8> > sig_a;
    sc_trace(trace_f, sig_a, "A");
    sc_signal<sc_uint<8> > sig_b;
    sc_trace(trace_f, sig_b, "B");
    sc_signal<sc_uint<8> > sig_pgcd;
    sc_trace(trace_f, sig_pgcd, "PGCD");

    // init PGCD module
    mod_pgcd_rtl pgcd_i("pgcd");
    pgcd_i.clk(clk);
    pgcd_i.valid(sig_valid);
    pgcd_i.a(sig_a);
    pgcd_i.b(sig_b);
    pgcd_i.ready(sig_ready);
    pgcd_i.pgcd(sig_pgcd);

    // simulation
    sig_valid = false;
    // fist calcul
    sig_a = 36;
    sig_b = 60;
    sc_start(2, SC_NS);
    sig_valid = true;
    sc_start(2, SC_NS);
    sig_valid = false;
    while(!sig_ready)
        sc_start(2, SC_NS);
    sc_uint<8> res = sig_pgcd;
    if(res == 12) cout << "First calcul finished successfuly" << endl;
    else cout << "First calcul error: sig_pgcd = " << res << " instead of 12" << endl;
    // second calcul
    sig_a = 42;
    sig_b = 63;
    sc_start(2, SC_NS);
    sig_valid = true;
    sc_start(2, SC_NS);
    sig_valid = false;
    while(!sig_ready)
        sc_start(1, SC_NS);
    res = sig_pgcd;
    if(res == 21) cout << "Second calcul finished successfuly" << endl;
    else cout << "Second calcul error: sig_pgcd = " << res << " instead of 21" << endl;

    sc_close_vcd_trace_file(trace_f);

    cout << "pgcd(36,60): " << pgcd_compute(36, 60) << endl;
    cout << "pgcd(42,63): " << pgcd_compute(42, 63) << endl;
    cout << "pgcd(357,561): " << pgcd_compute(357, 561) << endl;
    return 0;
}
