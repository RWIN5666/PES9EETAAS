cmake_minimum_required(VERSION 2.8)

set(PRJ zigBeeServer)
set(MAIN main/comXbee.c)

set(CMAKE_BUILD_TYPE Debug)
SET(CMAKE_C_FLAGS               "${CMAKE_C_FLAGS} -W -Wall -ansi -pedantic -std=c99 -Wfatal-errors")

project($PRJ)

include_directories(
	./include
)

add_subdirectory(src/serial0)
add_subdirectory(src/zigbee)

add_executable(${PRJ} ${MAIN})
target_link_libraries(${PRJ} serial0 zigbee)