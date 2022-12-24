cmake_minimum_required(VERSION 3.20)
project(woden)

set(CMAKE_CXX_STANDARD 17)
set(WODEN_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

file(GLOB WODEN_SOURCES "${WODEN_SOURCE_DIR}/**/*.cpp")

include_directories(${WODEN_SOURCE_DIR})

add_executable(woden ${WODEN_SOURCE_DIR}/main.cpp ${WODEN_SOURCES})
target_compile_options(woden PRIVATE -Wall)

install(TARGETS woden DESTINATION bin)
