cmake_minimum_required(VERSION 2.8)

add_library(serial0 SHARED serial0.c)

include_directories(serial0 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

