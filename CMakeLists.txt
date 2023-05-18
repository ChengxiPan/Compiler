cmake_minimum_required(VERSION 3.5)
project(jack_compiler)

include_directories (include)
set(CMAKE_CXX_STANDARD 17)

add_executable(jack_compiler src/main.cpp)