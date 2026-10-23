cmake_minimum_required(VERSION 3.31)

project(lib LANGUAGES C)

add_library(lib	STATIC
	include/base_c_types.h

	include/logs.h

	include/files.h
	source/files.c
)

target_include_directories(lib	PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/include
)
