cmake_minimum_required(VERSION 3.24)
project(NetFramework)

set(CMAKE_CXX_STANDARD 23)

include_directories(Core/FS)
include_directories(Core/HTTP)
include_directories(Core/NET)

add_executable(Core/FS/FS.cpp
               Core/FS/IFS.h
               Core/HTTP/HTTP.cpp
               Core/HTTP/IHTTP.h
               Core/NET/INET.h
               Core/NET/NET.cpp)
