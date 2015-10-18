cmake_minimum_required(VERSION 2.8)

add_library(serial SHARED serial0.c)

include_directories(serial PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

