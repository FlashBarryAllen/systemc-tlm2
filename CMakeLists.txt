cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(my_sc)

add_definitions(-DPROJECT_ROOT_DIR="${CMAKE_SOURCE_DIR}")

include_directories("${CMAKE_SOURCE_DIR}/include/")
include_directories("${CMAKE_SOURCE_DIR}/include/systemc/")
include_directories("${CMAKE_SOURCE_DIR}/include/spdlog/")
include_directories("${CMAKE_SOURCE_DIR}/include/gtest/")
include_directories("${CMAKE_SOURCE_DIR}/include/gmock/")
include_directories("${CMAKE_SOURCE_DIR}/include/tinyxml2/")
include_directories("${CMAKE_SOURCE_DIR}/modules/top/")
include_directories("${CMAKE_SOURCE_DIR}/modules/node/")
include_directories("${CMAKE_SOURCE_DIR}/modules/gen/")
include_directories("${CMAKE_SOURCE_DIR}/modules/memory/")
include_directories("${CMAKE_SOURCE_DIR}/modules/dmac/")
include_directories("${CMAKE_SOURCE_DIR}/modules/peq/")
include_directories("${CMAKE_SOURCE_DIR}/modules/islip/")
include_directories("${CMAKE_SOURCE_DIR}/modules/dpa/")
include_directories("${CMAKE_SOURCE_DIR}/modules/lsu/")
include_directories("${CMAKE_SOURCE_DIR}/test")

link_directories("${CMAKE_SOURCE_DIR}/libs/systemc/")
link_directories("${CMAKE_SOURCE_DIR}/libs/spdlog/")
link_directories("${CMAKE_SOURCE_DIR}/libs/gtest/")
link_directories("${CMAKE_SOURCE_DIR}/libs/gmock/")
link_directories("${CMAKE_SOURCE_DIR}/libs/tinyxml2/")


add_executable(${PROJECT_NAME} 
    ${CMAKE_SOURCE_DIR}/main.cpp
    ${CMAKE_SOURCE_DIR}/test/test.cpp
)

target_link_libraries(${PROJECT_NAME} debug gtest              optimized gtest)
target_link_libraries(${PROJECT_NAME} debug pthread            optimized pthread)
target_link_libraries(${PROJECT_NAME} debug libsystemc_debug.a optimized libsystemc.a)
target_link_libraries(${PROJECT_NAME} debug libspdlog.a        optimized libspdlog.a)
target_link_libraries(${PROJECT_NAME} debug libtinyxml2.a      optimized libtinyxml2.a)
