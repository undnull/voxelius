#
# CMakeLists.txt
# Created: 2021-01-16, 15:41:11.
# Copyright (C) 2021, Kirill GPRB.
#
target_sources(voxelius PRIVATE
    "${CMAKE_CURRENT_LIST_DIR}/main.cc")
add_subdirectory(data)
add_subdirectory(input)
add_subdirectory(render)
add_subdirectory(ui)
add_subdirectory(util)
