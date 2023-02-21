cmake_minimum_required(VERSION 3.16.3)
set(CMAKE_CXX_STANDARD 17)
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

file(GLOB examples RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "example/*.cpp")
foreach(file IN LISTS examples)
    get_filename_component(name ${file} NAME_WLE)
    message(STATUS ${name})
    add_executable("example_${name}" ${file})
    target_link_libraries("example_${name}" recycled_ptr)
endforeach(file)
