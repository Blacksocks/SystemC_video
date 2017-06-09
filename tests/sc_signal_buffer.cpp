#include <systemc.h>
#include <string>

SC_MODULE(receiver)
{
    sc_in<sc_uint<8> > in;
    std::string name;

    receiver(sc_module_name _name):sc_module(_name)
    {
        name = _name;
        SC_METHOD(receive);
        sensitive << in;
    }

    void receive()
    {
        cout << "[" << name << "] value: " << in << endl;
    }

    SC_HAS_PROCESS(receiver);
};

int sc_main(int argc, char * argv[])
{
    sc_trace_file * trace_f;
    trace_f = sc_create_vcd_trace_file("my_simu_trace");
    trace_f->set_time_unit(1, SC_NS);


    // init buffer and signal
    sc_buffer<sc_uint<8> > buffer_i;
    sc_signal<sc_uint<8> > signal_i;
    receiver receiver_1("receiver_buffer");
    receiver receiver_2("receiver_signal");
    receiver_1.in(buffer_i);
    receiver_2.in(signal_i);
    sc_trace(trace_f, signal_i, "signal");
    sc_trace(trace_f, buffer_i, "buffer");
    sc_uint<8> v0 = 0;
    sc_uint<8> v10 = 10;
    signal_i = v0;
    buffer_i = v0;
    sc_start(10, SC_NS);
    signal_i = v10;
    buffer_i = v10;
    sc_start(10, SC_NS);
    signal_i = v10;
    buffer_i = v10;
    sc_start(10, SC_NS);
    signal_i = v0;
    buffer_i = v0;
    sc_start(10, SC_NS);

    sc_close_vcd_trace_file(trace_f);

    return 0;
}
