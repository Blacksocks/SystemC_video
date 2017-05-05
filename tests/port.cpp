#include <systemc.h>

SC_MODULE(foo) {
   sc_in<bool> i;
   SC_CTOR(foo):i("i") {}
};
SC_MODULE(bar) {
   sc_out<bool> o;
   SC_CTOR(bar):o("o") {}
};

int sc_main(int argc, char * argv[])
{
   sc_signal<bool> s("s");

   foo foo_i("foo");
   bar bar_i("bar");

   // connexion
   foo_i.i(s);
   bar_i.o(s);

   return 0;
}
