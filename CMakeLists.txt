cmake_minimum_required(VERSION 3.24)
project(NetFramework)

set(CMAKE_CXX_STANDARD 23)

include_directories(Core/FS)
include_directories(Core/HTTP)
include_directories(Core/NET)

add_executable(NetFramework Core/FS/FS.cpp
               Core/HTTP/HTTP.cpp
               Core/NET/NET.cpp
               Core/SPtr.cpp Core/test_smart_pointers.cpp)
