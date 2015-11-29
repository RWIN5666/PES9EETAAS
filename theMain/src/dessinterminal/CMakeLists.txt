cmake_minimum_required(VERSION 2.8)

add_library(dessinterminal STATIC drawterminal.c)

include_directories(dessinterminal PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

