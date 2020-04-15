# CMakeList.txt: CMakeProject1 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)
project ("DICCLIENT")
add_definitions(-DUNICODE -D_UNICODE)
add_definitions(-DUNICODE -D_UNICODE)
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()
include_directories(../PIPE)
set(
SRC
../PIPE/pipe.h
../PIPE/pipe.cpp
DICCLIENT.cpp
)
# 将源代码添加到此项目的可执行文件。
add_executable (${PROJECT_NAME}  ${SRC})

# TODO: 如有需要，请添加测试并安装目标。