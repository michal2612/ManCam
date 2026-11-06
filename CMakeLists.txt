cmake_minimum_required(VERSION 3.28)
project(ManCam)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(${UNIX})
    add_compile_definitions(UNIX_LIKE)
endif()

add_subdirectory(src/libs/core)
add_subdirectory(src/exe/console)