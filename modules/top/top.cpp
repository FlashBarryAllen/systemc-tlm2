#include <top.h>

a::a(sc_module_name name) : sc_module(name) {
    SC_METHOD(run);
    sensitive << m_clk.pos();
    dont_initialize();
}

void a::run() {
    tlm_generic_payload trans;
    trans.set_command(TLM_WRITE_COMMAND);
    int data[4] = {0x12, 0x34, 0x56, 0x78};
    trans.set_data_ptr((unsigned char*)data);
    trans.set_data_length(4);
    tlm_phase phase = BEGIN_REQ;
    sc_time time = SC_ZERO_TIME;

    cout << "time: " << sc_time_stamp() << ", a::run()" << endl;

    snd->nb_transport_fw(trans, phase, time);
}

/*******************************************/
b::b(sc_module_name name) : sc_module(name) {
    SC_METHOD(run);
    sensitive << m_clk.pos();
    dont_initialize();

    rcv.register_nb_transport_fw(this, &b::rcv_from);
}

tlm_sync_enum b::rcv_from(tlm_generic_payload& trans, tlm_phase& phase, sc_time& time) {
    unsigned char * data = trans.get_data_ptr();
    cout << "time: " << sc_time_stamp() << ", data[0]" << endl;
    return TLM_COMPLETED;
}

void b::run() {

    cout << "time: " << sc_time_stamp() << ", b::run()" << endl;
}

top::top(sc_module_name name) : AA("aa"), BB("bb"), m_clk("clk", 1, SC_NS) {
    AA.m_clk(m_clk);
    BB.m_clk(m_clk);
    AA.snd.bind(BB.rcv);
}