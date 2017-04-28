#include <systemc.h>

int sc_main (int argc, char * argv[])
{
    // tests on logic vectors
    cout << "> Tests on logic vectors" << endl;
    sc_lv<0> lv1();
    sc_lv<1> lv2(3);
    sc_lv<2> lv3("12");
    sc_lv<4> lv4("0123");
    sc_lv<3> lv5((lv3, lv4[0]));
    cout << "12 + 3: " << lv5 << endl;
    sc_lv<4> lv6("23");
    sc_lv<5> lv7("0123");
    cout << "23 stored on an 4-size vector: " << lv6 << endl;
    cout << "0123 && 12: " << (lv4 & lv3) << endl;
    lv4(2, 0) = "111";
    cout << "0111 and_reduce(): " << lv4.and_reduce() << endl;
    cout << "1111 and_reduce(): " << sc_lv<4>("1111").and_reduce() << endl;
    cout << "1111 xnor_reduce(): " << sc_lv<4>("1111").xnor_reduce() << endl;
    cout << "conversion into integer : " << lv7 << " -> " << lv7.to_int() << endl;
    cout << endl;

    // tests on bit vectors
    cout << "> Tests on bit vectors" << endl;
    sc_bv<1> bv1(true);
    sc_bv<1> bv2(0);
    sc_bv<1> bv3('0');
    sc_bv<1> bv4("1");
    sc_bv<8> bv5("101001");
    bv5[2] = true;
    cout << "bv5 = 00101001, bv5[2] = true, bv5 = " << bv5 << endl;
    sc_bv<8> bv6 = true;
    cout << "bv6 = true, bv6: " << bv6 << endl;
    sc_bv<8> bv7 = false;
    cout << "bv7 = false, bv7: " << bv7 << endl;
    int i1 = bv6.to_int();
    uint64_t i2 = bv5.to_uint64();
    cout << "conversion into integer : " << bv4 << " -> " << i1 << endl;
    cout << "conversion into uint64_t: " << bv5 << " -> " << i2 << endl;
    return 0;
}
