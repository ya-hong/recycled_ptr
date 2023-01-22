cmake_minimum_required(VERSION 3.16.3)
set(CMAKE_CXX_STANDARD 14)
project(recycled_ptr)

# file(GLOB files RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}/src *)
# aux_source_directory(./ sources)
file(GLOB sources RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "src/*.cpp")


message(STATUS sources)
foreach(file IN LISTS sources)
    message(STATUS ${file})
endforeach(file)

include_directories(include)

add_library(recycled_ptr SHARED ${sources})

add_executable(test example/test.cpp)
target_link_libraries(test PUBLIC recycled_ptr)
