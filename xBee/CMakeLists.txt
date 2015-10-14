cmake_minimum_required(VERSION 2.6)
set(CMAKE_BUILD_TYPE Debug)

project(comXbee)
#librairies a inclure
include_directories(/home/erwin/Documents/PROJETELEC/Tests/comXbee/include/)
#
# Global C_FLAGS
#
SET(CMAKE_C_FLAGS               "${CMAKE_C_FLAGS} -W -Wall -ansi -pedantic -std=c99 -Wfatal-errors")
# liste des fichiers source
file(
	GLOB_RECURSE
	source_files
	src/*
)
#fichier executable
add_executable(
	comXbee
	${source_files}
)
#edition de lien entre le programme et les librairies
#target_link_libraries(
#	comXbee
#)