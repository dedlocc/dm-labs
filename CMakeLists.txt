cmake_minimum_required(VERSION 3.17)
project(dm-labs)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE FILES src/**.cpp)

foreach (FILE ${FILES})
    file(RELATIVE_PATH FILE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/src/ ${FILE})
    get_filename_component(FILE_DIR ${FILE_PATH} DIRECTORY)
    get_filename_component(FILE_NAME ${FILE_PATH} NAME_WE)
    string(REPLACE / "." TARGET "${FILE_DIR}.${FILE_NAME}")
    add_executable(${TARGET} ${FILE})
endforeach ()
