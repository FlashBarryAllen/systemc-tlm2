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

class top_tlm : public sc_module {
    public:
        SC_HAS_PROCESS(top_tlm);
        top_tlm(sc_module_name name);
        a AA;
        b BB;
    
    public:
        sc_clock m_clk;
};

class producer : public sc_module {
public:
    SC_HAS_PROCESS(producer);

    // 原生 sc_port 绑定到 sc_fifo 的写入端
    //sc_port<sc_fifo_out_if<int>> out_port;
    sc_fifo_out<int> out_port;

    producer(sc_module_name name) : sc_module(name) {
        SC_THREAD(main_thread);
    }

private:
    void main_thread() {
        for (int i = 0; i < 5; i++) {
            wait(10, SC_NS);
            out_port->write(i * 10);  // 通过端口调用 fifo 的 write
            cout << "[" << sc_time_stamp() << "] Producer: wrote " << i * 10 << endl;
        }
    }
};

class consumer : public sc_module {
public:
    SC_HAS_PROCESS(consumer);

    // 原生 sc_port 绑定到 sc_fifo 的读取端
    //sc_port<sc_fifo_in_if<int>> in_port;
    sc_fifo_in<int> in_port;

    consumer(sc_module_name name) : sc_module(name) {
        SC_THREAD(main_thread);
    }

private:
    void main_thread();
};

class top : public sc_module {
public:
    producer prod;
    consumer cons;
    
    // 原生 sc_fifo 通道
    sc_fifo<int> fifo;

    top(sc_module_name name) 
        : sc_module(name),
          prod("producer"),
          cons("consumer"),
          fifo("fifo", 4)  // 深度为 4 的 FIFO
    {
        // 绑定端口到 fifo 的对应接口
        prod.out_port(fifo);   // sc_fifo_out_if<int>
        cons.in_port(fifo);    // sc_fifo_in_if<int>
    }
};

 #endif