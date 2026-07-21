#include "test.h"
#include <iomanip>
#include <map>

void TEST_aaa() {
    std::cout << "aaa" << std::endl;
}

void TEST_top() {
    top my_top("my_top");
    sc_start(20, sc_core::SC_NS);
}