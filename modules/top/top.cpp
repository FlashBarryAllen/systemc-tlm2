#include <top.h>

producer::producer(sc_module_name name) : m_data(100) {
    SC_THREAD(run);
    //sensitive << m_clk.pos();
    //dont_initialize();
}

producer::~producer() {

}

void producer::run() {
    int data = 0;
    while (true) {
        data = m_data + 100;
        m_data = data;
        tx->nb_write(data);
        cout << "tim: " << sc_time_stamp() << ", write data= " << data << endl;
        wait(1, SC_NS);
    }
}

consumer::consumer(sc_module_name name) {
    SC_THREAD(run);
    //sensitive << m_clk.pos();
    //dont_initialize();
}

consumer::~consumer() {

}

void consumer::run() {
    int data = 0;
    while (true) {
        if (rx->nb_read(data)) {
            cout << "tim: " << sc_time_stamp() << ", read data= " << data << endl;
        }
        wait(1, SC_NS);
    }
}

top::top(sc_module_name name) : pro("producer"), con("consumer"), m_clk("clock", 1, SC_NS) {
    pro.m_clk(m_clk);
    con.m_clk(m_clk);
    pro.tx(fifo);
    con.rx(fifo);
}

top::~top() {

}