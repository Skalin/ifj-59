cmake_minimum_required(VERSION 3.6)
project(ifj_59)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -pedantic -lm")

set(SOURCE_FILES main.c lexical_analyzer.c error_handler.c expressions.c garbage_collector.c ial.c interpret.c instrstack.c parser.c stack.c typedef.h)

add_executable(ifj_59 ${SOURCE_FILES})
