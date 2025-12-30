cmake_minimum_required(VERSION 3.25)
project(ISM)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)

add_executable(main)

target_sources(main PRIVATE  
    main.cpp
)

add_subdirectory(src)