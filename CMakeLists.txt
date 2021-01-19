#
# CMakeLists.txt
# Created: 2021-01-16, 15:11:18.
# Copyright (C) 2021, Kirill GPRB.
#
cmake_minimum_required(VERSION 3.10)
project(voxelius VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
add_executable(voxelius "")

add_subdirectory(shaders)

# warning C4996: This function or variable may be unsafe.
target_compile_definitions(voxelius PRIVATE _CRT_SECURE_NO_WARNINGS=1)

add_subdirectory(external)
add_subdirectory(include)
add_subdirectory(src)
