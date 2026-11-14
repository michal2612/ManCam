cmake_minimum_required(VERSION 3.28)
project(ManCam)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(${UNIX})
    add_compile_definitions(UNIX_LIKE)
else()
    message(FATAL_ERROR "Only Unix systems are supported")
endif()

enable_testing()

add_subdirectory(dependencies/googletest)

add_subdirectory(src/libs/core)
add_subdirectory(src/libs/core/tests)
add_subdirectory(src/exe/console)