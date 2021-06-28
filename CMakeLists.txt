cmake_minimum_required(VERSION 3.4...3.18)
project(opencrg)

add_subdirectory(pybind11)
add_subdirectory(opencrg-c-api)

pybind11_add_module(opencrg src/opencrg.h src/opencrg.cc src/py_opencrg.cpp)
target_link_libraries(opencrg PRIVATE opencrg-c-api)

# EXAMPLE_VERSION_INFO is defined by setup.py and passed into the C++ code as a
# define (VERSION_INFO) here.
target_compile_definitions(opencrg PRIVATE VERSION_INFO=${EXAMPLE_VERSION_INFO})
