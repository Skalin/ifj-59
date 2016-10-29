cmake_minimum_required(VERSION 3.6)
project(ifj_59)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -Wall -Werror")

set(SOURCE_FILES main.c main.h lexical_analyzer.c lexical_analyzer.h garbage_collector.c garbage_collector.h error_handler.c error_handler.h)

add_executable(ifj_59 ${SOURCE_FILES})
