#include <systemc.h>

SC_MODULE(foo) {
	sc_in <bool> i;
	sc_out<bool> o;
	SC_CTOR(foo):i("i"),o("o") {}
};

SC_MODULE(bar) {
	sc_in <bool> i;
	sc_out<bool> o;
	SC_CTOR(bar):i("i"),o("o") {}
};

SC_MODULE(foobar)
{
	// entrée/sortie
	sc_in <bool> i;
	sc_out<bool> o;
	// interne
	sc_signal<bool> s;
	// sous modules
	foo foo_i;
	bar bar_i;

	SC_CTOR(foobar)
		:i("i"),o("o"),s("s"),
		foo_i("foo"), bar_i("bar")
	{
		// connexions aux I/O
		foo_i.i(i);
		bar_i.o(o);
		// connexion interne
		foo_i.o(s);
		bar_i.i(s);
	}
};

int sc_main(int argc, char * argv[])
{
	sc_trace_file *trace_f;
	trace_f = sc_create_vcd_trace_file ("my_simu_trace");
	trace_f->set_time_unit(1, SC_NS);

  // horloge de période 10ns
  sc_clock ck1("ck1", 10, SC_NS);
  sc_trace(trace_f, ck1, "ck10");

	sc_signal<bool> o("o");
  sc_trace(trace_f, o, "output");

	foobar uut("foobar");

	uut.i(ck1);
	uut.o(o);

  sc_start(1000, SC_NS);

  sc_close_vcd_trace_file(trace_f);

	return 0;
}
