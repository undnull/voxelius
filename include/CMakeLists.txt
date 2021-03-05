#
# CMakeLists.txt
# Created: 2021-01-16, 15:28:02.
# Copyright (C) 2021, Kirill GPRB.
#
target_include_directories(voxelius PRIVATE "${CMAKE_CURRENT_LIST_DIR}")
configure_file("${CMAKE_CURRENT_LIST_DIR}/config.hh.in" "${CMAKE_CURRENT_LIST_DIR}/config.hh" @ONLY)
