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

// make sum of two pixels using method
SC_MODULE(sum_method)
{
	sc_in<Pixel> p1;
	sc_in<Pixel> p2;
	sc_out<Pixel> pSum;

	SC_CTOR(sum_method):p1("p1"),p2("p2"),pSum("pSum")
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
		if(p1_.r + p2_.r >= 32)
			pSum_.r = 31;
		pSum_.g = p1_.g + p2_.g;
		if(p1_.g + p2_.g >= 64)
			pSum_.g = 63;
		pSum_.b = p1_.b + p2_.b;
		if(p1_.b + p2_.b >= 32)
			pSum_.b = 31;
		pSum = pSum_;
	}
};

// make sum of two pixels using thread
SC_MODULE(sum_thread)
{
	sc_in<Pixel> p1;
	sc_in<Pixel> p2;
	sc_out<Pixel> pSum;

	void compute_sum()
	{
	    while(1)
		{
			wait();
			Pixel pSum_;
			Pixel p1_ = p1;
			Pixel p2_ = p2;
			pSum_.r = p1_.r + p2_.r;
			if(p1_.r + p2_.r >= 32)
				pSum_.r = 31;
			pSum_.g = p1_.g + p2_.g;
			if(p1_.g + p2_.g >= 64)
				pSum_.g = 63;
			pSum_.b = p1_.b + p2_.b;
			if(p1_.b + p2_.b >= 32)
				pSum_.b = 31;
			pSum = pSum_;
		}
	}

	SC_CTOR(sum_thread)
	{
		SC_THREAD(compute_sum);
		sensitive << p1 << p2;
	}
};

// display all colors using method
SC_MODULE(colors_method)
{
	sc_in<bool> clk;
	sc_out<Pixel> p;

	SC_CTOR(colors_method):clk("clk"), p("p")
	{
		SC_METHOD(inc_color);
		sensitive << clk.pos();
	}

	void inc_color()
	{
		Pixel p_ = p;
		if(p_.r < 31)
			p_.r++;
		else if(p_.g < 63)
			p_.g++;
		else if(p_.b < 31)
			p_.b++;
		p = p_;
	}
};

// display all colors using thread
SC_MODULE(colors_thread)
{
	sc_in<bool> clk;
	sc_out<Pixel> p;

	SC_CTOR(colors_thread):clk("clk"), p("p")
	{
		SC_THREAD(inc_color);
		sensitive << clk.pos();
	}

	void inc_color()
	{
		while(1)
		{
			wait();
			Pixel p_ = p;
			if(p_.r < 31)
				p_.r++;
			else if(p_.g < 63)
				p_.g++;
			else if(p_.b < 31)
				p_.b++;
			p = p_;
		}
	}
};

// display all colors using cthread
SC_MODULE(colors_cthread)
{
	sc_in<bool> clk;
	sc_out<Pixel> p;

	SC_CTOR(colors_cthread):clk("clk"), p("p")
	{
		SC_CTHREAD(inc_color, clk.pos());
	}

	void inc_color()
	{
		while(1)
		{
			wait();
			Pixel p_ = p;
			if(p_.r < 31)
				p_.r++;
			else if(p_.g < 63)
				p_.g++;
			else if(p_.b < 31)
				p_.b++;
			p = p_;
		}
	}
};

int sc_main (int argc, char * argv[])
{
	sc_trace_file *trace_f;
	trace_f = sc_create_vcd_trace_file ("my_simu_trace");
	trace_f->set_time_unit(1, SC_NS);

	Pixel p;
	// init des pixels 1, 2, 3 et sum
	sc_signal<Pixel> sig_p1;
	sc_trace(trace_f, sig_p1, "pixel_1");
	sc_signal<Pixel> sig_p2;
	sc_trace(trace_f, sig_p2, "pixel_2");
	sc_signal<Pixel> sig_p3;
	sc_trace(trace_f, sig_p3, "pixel_3");
	sc_signal<Pixel> sig_pSum;
	sc_trace(trace_f, sig_pSum, "pixel_sum");
	// init de la clock
	sc_clock clk("clk", 2, SC_NS);
	sc_trace(trace_f, clk, "clk");

	// creation du module de somme
	sum_thread sum_i("sum");
	sum_i.p1(sig_p1);
	sum_i.p2(sig_p2);
	sum_i.pSum(sig_pSum);
	// creation du module d'incrementation
	colors_cthread colors_i("colors");
	colors_i.clk(clk);
	colors_i.p(sig_p3);

	sig_p1 = p;
	sig_p2 = p;
	sig_p3 = p;
	sc_start(64, SC_NS);
	p.r = 9;
	p.g = 8;
	p.b = 7;
	sig_p1 = p;
	sc_start(64, SC_NS);
	p.r = 31;
	p.g = 63;
	p.b = 31;
	sig_p2 = p;
	sc_start(128, SC_NS);

	sc_close_vcd_trace_file(trace_f);
	return 0;
}
