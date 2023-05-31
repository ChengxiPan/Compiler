cmake_minimum_required(VERSION 3.25)
project(jack_compiler)

include_directories (include)
set(CMAKE_CXX_STANDARD 17)

add_executable(compiler src/Scanner.cpp src/main.cpp)