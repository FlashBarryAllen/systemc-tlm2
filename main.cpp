#include "test.h"
#include "top.h"
#include "gen.h"
#include "gtest/gtest.h"
#include <tlm_utils/simple_target_socket.h>

using ::testing::EmptyTestEventListener;
using ::testing::InitGoogleTest;
using ::testing::Test;
using ::testing::TestEventListeners;
using ::testing::TestInfo;
using ::testing::TestPartResult;
using ::testing::UnitTest;


int sc_main(int argc, char* argv[])
{
    InitGoogleTest(&argc, argv);

    TEST_aaa();
    TEST_top();
    //top my_top("my_top");
    //sc_start(20, sc_core::SC_NS);
    std::cout << "done" << std::endl;

    return 0;
}