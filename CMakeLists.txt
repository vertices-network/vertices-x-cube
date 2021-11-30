cmake_minimum_required(VERSION 3.19)

if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
message(STATUS "Pulling ARM GCC toolchain using default toolchain file")
include(utils/cmake/arm-gcc-toolchain.cmake)
endif()

include(utils/cmake/utils.cmake)

project(vertices_STM32Cube C)

set(CMAKE_C_STANDARD 11)

add_subdirectory(Middlewares/Third_Party/c-vertices-sdk/)

add_subdirectory(Projects/B-L4S5I-IOT01A/Applications/vertices-client)
