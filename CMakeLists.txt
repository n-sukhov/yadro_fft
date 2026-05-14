cmake_minimum_required(VERSION 3.16)

project(yadro_fft LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(headers_dir ./include)
set(source_dir ./src)

set(sources
    ${source_dir}/main.cpp
    ${source_dir}/fft.cpp
)

add_executable(yadro_fft ${sources})

target_include_directories(yadro_fft PRIVATE ${headers_dir})