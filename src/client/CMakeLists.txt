#
# CMakeLists.txt
# Created: 2021-01-30, 17:34:47
# Copyright (C) 2021, Kirill GPRB.
#
target_sources(voxelius PRIVATE
    "${CMAKE_CURRENT_LIST_DIR}/client.cc"
    "${CMAKE_CURRENT_LIST_DIR}/mesh.cc"
    "${CMAKE_CURRENT_LIST_DIR}/renderer.cc"
    "${CMAKE_CURRENT_LIST_DIR}/resources.cc"
    "${CMAKE_CURRENT_LIST_DIR}/window.cc"
)
add_subdirectory(gl)
