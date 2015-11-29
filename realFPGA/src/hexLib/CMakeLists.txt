cmake_minimum_required(VERSION 2.8)

add_library(hexLib STATIC hexLib.c)

include_directories(hexLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

