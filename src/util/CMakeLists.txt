#
# CMakeLists.txt
# Created: 2021-01-16, 21:39:14.
# Copyright (C) 2021, Kirill GPRB.
#
target_sources(voxelius PRIVATE
    "${CMAKE_CURRENT_LIST_DIR}/clock.cc"
    "${CMAKE_CURRENT_LIST_DIR}/command_line.cc"
    "${CMAKE_CURRENT_LIST_DIR}/fs.cc"
    "${CMAKE_CURRENT_LIST_DIR}/logger.cc")
