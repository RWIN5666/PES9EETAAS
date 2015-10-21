cmake_minimum_required(VERSION 2.8)

add_library(zigbee SHARED zigbeeLib.c checksum.c)

include_directories(zigbee PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

