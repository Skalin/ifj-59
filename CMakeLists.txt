cmake_minimum_required(VERSION 3.6)
project(ifj_59)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -Wall -Werror -pedantic")

set(SOURCE_FILES lexical_analyzer.c error_handler.c expressions.c garbage_collector.c generator.c ial.c interpret.c iStack.c parser.c stack.c typedef.h)

add_executable(ifj_59 ${SOURCE_FILES})
