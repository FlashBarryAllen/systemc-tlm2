#ifndef TOP_H
#define TOP_H

#include <systemc>
#include <tlm>

using namespace std;
using namespace tlm;
using namespace sc_core;

class producer : public sc_module {
public:
    SC_HAS_PROCESS(producer);
    producer(sc_module_name name);
    ~producer();

    void run();
public:
    sc_in_clk m_clk;
    sc_fifo_out<int> tx;
    int m_data;
};

class consumer : public sc_module {
public:
    SC_HAS_PROCESS(consumer);
    consumer(sc_module_name name);
    ~consumer();

    void run();

public:
    sc_in_clk m_clk;
    sc_fifo_in<int> rx;
};

class top : public sc_module {
public:
    SC_HAS_PROCESS(top);
    top(sc_module_name name);
    ~top();

public:
    sc_clock m_clk;
    producer pro;
    consumer con;
    sc_fifo<int> fifo;
};

 #endif