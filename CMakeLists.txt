cmake_minimum_required(VERSION 3.10)
project(rlc_solver)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)

file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "include/*.hpp")
file(GLOB_RECURSE HEADERS "dependencies/*.hpp")

add_executable(rlc_solver ${SOURCES})