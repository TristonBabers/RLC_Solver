cmake_minimum_required(VERSION 3.10)
project(rlc_solver)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)

file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "include/*.hpp")
file(GLOB_RECURSE HEADERS "dependencies/*.hpp")

add_executable(rlc_solver ${SOURCES})

# Add full static linking flags
set_target_properties(rlc_solver PROPERTIES
    LINK_FLAGS "-static -static-libstdc++ -static-libgcc"
)