cmake_minimum_required(VERSION 3.17)
project(dm-labs)

set(CMAKE_CXX_STANDARD 17)

file(GLOB FILES term4/turing/src/*.cpp)

foreach (FILE ${FILES})
    get_filename_component(TARGET ${FILE} NAME_WE)
    add_executable(${TARGET} ${FILE})
endforeach ()

add_compile_definitions(LOCAL)
