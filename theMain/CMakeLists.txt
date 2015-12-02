cmake_minimum_required(VERSION 2.8)

set(PRJ serverExecutable)
set(MAIN main/main.c)

set(PRJ2 fpgaExecutable)
set(TEST main/dummyFpga.c)



set(CMAKE_BUILD_TYPE Debug)
SET(CMAKE_C_FLAGS               "${CMAKE_C_FLAGS} -W -Wall -Wno-pointer-sign -ansi -pedantic -std=c99 -Wfatal-errors")

project($PRJ)

include_directories(
	./include
)

add_subdirectory(src/dessinterminal)
add_subdirectory(src/serial0)
add_subdirectory(src/zigbee)
add_subdirectory(src/hexLib)


add_executable(${PRJ} ${MAIN})
#add_executable(${PRJ2} ${TEST})
target_link_libraries(${PRJ} pthread serial0 zigbee dessinterminal hexLib ${CMAKE_CURRENT_SOURCE_DIR}/lib/jansson/libjansson.a)
#target_link_libraries(${PRJ2} pthread serial0 zigbee dessinterminal hexLib)

