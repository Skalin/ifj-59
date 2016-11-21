cmake_minimum_required(VERSION 3.6)
project(ifj_59)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -Wall -Werror -pedantic")

set(SOURCE_FILES main.c main.h ial.c ial.h lexical_analyzer.c lexical_analyzer.h garbage_collector.c garbage_collector.h error_handler.c error_handler.h generator.h parser.c parser.h stack.c stack.h typedef.h expressions.c expressions.h)

add_executable(ifj_59 ${SOURCE_FILES})
