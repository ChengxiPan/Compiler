cmake_minimum_required(VERSION 3.25)
project(Java_Compiler)
set(CMAKE_CXX_STANDARD 17)

# 设置输出路径
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/output")
# 头文件库
include_directories (include)
# 在 src 目录下查找所有的源文件
aux_source_directory (src JAVA_LIB_SRC)
# 将所有可执行文件链接到一个静态库中,并编译
add_library (javalib "${JAVA_LIB_SRC}")
# 将编译出的文件放在一个java.cpp中
add_executable (${PROJECT_NAME} src/java.cpp)
target_link_libraries (${PROJECT_NAME} javalib) #将jacklib链接到可执行文件
