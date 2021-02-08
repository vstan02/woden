cmake_minimum_required(VERSION 3.17)
project(woden)

set(CMAKE_CXX_STANDARD 17)

set(WODEN_HEADERS)
set(WODEN_SOURCES)
set(WODEN_TESTS)

add_executable(Main src/main.cpp ${WODEN_SOURCES} ${WODEN_HEADERS})
# add_executable(Test ${WODEN_TESTS} ${WODEN_SOURCES} ${WODEN_HEADERS})

# GTest
# find_package(GTest CONFIG REQUIRED)
# enable_testing()
# add_test(All Test)
# target_link_libraries(Test PRIVATE GTest::gtest_main)
