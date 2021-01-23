#
# CMakeLists.txt
# Created: 2021-01-20, 14:13:11.
# Copyright (C) 2021, Kirill GPRB.
#
add_library(stb STATIC "${CMAKE_CURRENT_LIST_DIR}/stb.c")
target_include_directories(stb PRIVATE "${CMAKE_CURRENT_LIST_DIR}/stb/")
target_include_directories(stb PUBLIC "${CMAKE_CURRENT_LIST_DIR}/stb/")
