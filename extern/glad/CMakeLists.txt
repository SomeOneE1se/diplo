######  16.06.2026  p@nsk
######  glad cmake file
###############################################################################
cmake_minimum_required(VERSION 3.31 FATAL_ERROR)

project(glad)

add_library(glad    STATIC
    include/glad/glad.h
    src/glad.c
)

target_include_directories(glad PUBLIC  include/)
