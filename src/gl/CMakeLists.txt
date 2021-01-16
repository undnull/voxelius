#
# CMakeLists.txt
# Created: 2021-01-16, 18:56:42.
# Copyright (C) 2021, Kirill GPRB.
#
target_sources(voxelius PRIVATE
    "${CMAKE_CURRENT_LIST_DIR}/buffer.cc"
    "${CMAKE_CURRENT_LIST_DIR}/program.cc"
    "${CMAKE_CURRENT_LIST_DIR}/shader.cc"
    "${CMAKE_CURRENT_LIST_DIR}/vao.cc"
)
