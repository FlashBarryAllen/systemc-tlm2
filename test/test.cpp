#include "test.h"
#include <iomanip>
#include <map>

void TEST_aaa() {
    std::cout << "aaa" << std::endl;
}

void TEST_top() {
    top top("top");
    sc_start(20, SC_NS);
}
