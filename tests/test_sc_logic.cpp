#include <systemc.h>

int sc_main (int argc, char * argv[])
{
    sc_logic var1(0);
    sc_logic var2(1);
    sc_logic var3(true);
    sc_logic var4(false);
    sc_logic var5('0');
    sc_logic var6('1');
    sc_logic var7;
    sc_logic var8('Z');
    var7 = 'X';
    sc_logic var0;
    cout << "undefined variable value is: " << var0 << endl;
    cout << "0 & 1: " << (var1 & var2) << endl;
    cout << "0 | 1: " << (var1 | var2) << endl;
    cout << "0 ^ 1: " << (var1 ^ var2) << endl;
    cout << "~ 0  : " << (~var1) << endl;
    cout << "0 & true : " << (var1 & true) << endl;
    cout << "false | 1: " << (false | var2) << endl;
    cout << "0 ^ true : " << (var1 ^ true) << endl;
    bool b1 = var1.to_bool();
    char c1 = var2.to_char();
    bool b2 = var3.is_01();
    cout << "0 converted using to_bool(): " << b1 << endl;
    cout << "1 converted using to_char(): " << c1 << endl;
    cout << "1 converted using is_01()  : " << b2 << endl;
    return 0;
}
