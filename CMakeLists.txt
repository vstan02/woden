cmake_minimum_required(VERSION 3.17)
project(woden)

set(CMAKE_CXX_STANDARD 17)

set(
    WODEN_HEADERS
    src/Token.hpp
    src/Scanner.hpp
    src/Parser.hpp
    src/Expression.hpp
)

set(
    WODEN_SOURCES
    src/Scanner.cpp
    src/Parser.cpp
)

set(
    WODEN_TESTS
    src/ScannerTest.cpp
)

add_executable(Main src/main.cpp ${WODEN_SOURCES} ${WODEN_HEADERS})
add_executable(Test ${WODEN_TESTS} ${WODEN_SOURCES} ${WODEN_HEADERS})

#GTest
find_package(GTest CONFIG REQUIRED)
enable_testing()
add_test(All Test)
target_link_libraries(Test PRIVATE GTest::gtest_main)
