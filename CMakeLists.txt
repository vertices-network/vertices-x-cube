cmake_minimum_required(VERSION 3.19)
project(vertices_STM32Cube C)

set(CMAKE_C_STANDARD 11)

add_subdirectory(Middlewares/Third_Party/c-vertices-sdk/)

include(utils/cmake/utils.cmake)
add_subdirectory(Projects/B-L4S5I-IOT01A/Applications/vertices-client)
