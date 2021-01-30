#
# CMakeLists.txt
# Created: 2021-01-16, 15:41:11.
# Copyright (C) 2021, Kirill GPRB.
#
target_sources(voxelius PRIVATE
    "${CMAKE_CURRENT_LIST_DIR}/cmdline.cc"
    "${CMAKE_CURRENT_LIST_DIR}/globals.cc"
    "${CMAKE_CURRENT_LIST_DIR}/logger.cc"
    "${CMAKE_CURRENT_LIST_DIR}/main.cc"
)

add_subdirectory(client)
add_subdirectory(util)
