#include "test.h"
#include <iomanip>
#include <map>

void TEST_aaa() {
    cout << "************TEST_aaa************" << endl;
    cout << "aaa" << endl;
}

void TEST_top() {
    cout << "*************TEST_top***********" << endl;
    top my_top("my_top");
    sc_start(200, sc_core::SC_NS);
}