#include <systemc.h>

int sc_main (int argc, char * argv[])
{
    // tests on int and uint
    cout << "> Tests on int and uint" << endl;
    //sc_int<2> var1();
	cout << "default value: " << "-> always true" << endl;
    //sc_int<0> var2(3);
	cout << "size 0: " << "-> impossible" << endl;
    sc_int<2> var3(12);
	cout << "overflow: (12 on 2 bits)" << var3 << endl;
    sc_uint<8> var4(-12);
	cout << "negatif on unsigned (-12 on uint8): " << var4 << endl;
    sc_int<8> var5(23);
	cout << "var5 (=23): " << sc_bv<8>(23) << endl;
    sc_int<9> var6((var5, var5[0]));
	cout << "selection and concatenation (var5 = 23, (var5, var5[0])): " << var6 << endl;
    sc_int<5> var7(var5(2, 1));
    cout << "wide selection var5(2, 1): " << var7 << endl;
    cout << "23 && 121: " << (var5 & 121) << endl;
    var5(3, 1) = "111";
	sc_uint<4> var8 = "7";
	cout << "var5 = 23, var5(2, 0) = \"111\": " << var5 << endl;
    cout << "0111 and_reduce(): " << var8.and_reduce() << endl;
	var5 = 3;
	var5[7] = 1;
	cout << "set first bit (var5 = 3, var5[3] = 1): " << var5 << endl;
	sc_lv<8> var9("123");
	sc_int<8> var11 = var9;
	sc_uint<8> var10 = var9;
    cout << "init from sc_lv (123): " << var10 << endl;
    var9 = var10;
	cout << "conversion into sc_lv : " << var10 << " -> " << var9 << endl;
    cout << endl;
    return 0;
}
