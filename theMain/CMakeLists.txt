cmake_minimum_required(VERSION 2.8)

set(PRJ 42main)
set(MAIN main/main.c)

set(CMAKE_BUILD_TYPE Debug)
SET(CMAKE_C_FLAGS               "${CMAKE_C_FLAGS} -W -Wall -ansi -pedantic -std=c99 -Wfatal-errors")

project($PRJ)

include_directories(
	./include
)

add_subdirectory(src/dessinterminal)
add_subdirectory(src/serial0)
add_subdirectory(src/zigbee)
add_subdirectory(src/hexLib)


add_executable(${PRJ} ${MAIN})
target_link_libraries(${PRJ} pthread serial0 zigbee dessinterminal hexLib)

