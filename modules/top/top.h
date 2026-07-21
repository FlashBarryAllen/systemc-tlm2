#ifndef TOP_H
#define TOP_H
#include <tlm>
#include <tlm_utils/simple_initiator_socket.h>
#include <tlm_utils/simple_target_socket.h>

using namespace std;
using namespace sc_core;
using namespace tlm;
using namespace tlm_utils;

class a : public sc_module {
    public:
        SC_HAS_PROCESS(a);
        a(sc_module_name name);

    public:
        void run();
        sc_in_clk m_clk;
        simple_initiator_socket<a> snd;
};

class b : public sc_module {
    public:
        SC_HAS_PROCESS(b);
        b(sc_module_name name);

    public:
        void run();
        tlm_sync_enum rcv_from(tlm_generic_payload& trans, tlm_phase& phase, sc_time& time);
        sc_in_clk m_clk;
        simple_target_socket<b> rcv;
};

class top : public sc_module {
    public:
        SC_HAS_PROCESS(top);
        top(sc_module_name name);
        a AA;
        b BB;
    
    public:
        sc_clock m_clk;
};

 #endif