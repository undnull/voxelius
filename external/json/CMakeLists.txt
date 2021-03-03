#
# CMakeLists.txt
# Created: 2021-03-03, 19:51:23.
# Copyright (C) 2021, Kirill GPRB.
#
cmake_minimum_required(VERSION 3.10)
project(json VERSION 3.9.1 LANGUAGES CXX)
add_library(json INTERFACE)
target_include_directories(json INTERFACE "${CMAKE_CURRENT_LIST_DIR}")
