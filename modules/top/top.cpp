#include <top.h>

producer::producer(sc_module_name name) : m_data(100) {
    SC_METHOD(run);
    sensitive << m_clk.pos();
    dont_initialize();
}

producer::~producer() {

}

void producer::run() {
    int data = m_data + 100;
    m_data = data;
    tx->write(data);
    cout << "tim: " << sc_time_stamp() << ", write data= " << data << endl;
}

consumer::consumer(sc_module_name name) {
    SC_METHOD(run);
    sensitive << m_clk.pos();
    dont_initialize();
}

consumer::~consumer() {

}

void consumer::run() {
    int data = 0;
    if (rx->nb_read(data)) {
        cout << "tim: " << sc_time_stamp() << ", read data= " << data << endl;
    } else {
        next_trigger(rx->data_written_event());
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