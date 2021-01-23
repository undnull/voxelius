#
# CMakeLists.txt
# Created: 2021-01-16, 15:25:33.
# Copyright (C) 2021, Kirill GPRB.
#
add_library(glad STATIC "${CMAKE_CURRENT_LIST_DIR}/glad.c")
target_include_directories(glad PRIVATE "${CMAKE_CURRENT_LIST_DIR}/include/")
target_include_directories(glad PUBLIC "${CMAKE_CURRENT_LIST_DIR}/include/")
