cmake_minimum_required(VERSION 3.16)

project(Centralised-Performance-Monitor)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set default build type to Debug if none is specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the build type" FORCE)
endif()

include_directories(monitor collectors)

add_executable(monitor 
main.cpp 
collectors/cpu_collector.cpp
collectors/memory_collector.cpp
collectors/process_collector.cpp)