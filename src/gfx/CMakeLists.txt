#
# CMakeLists.txt
# Created: 2021-03-01, 21:22:29.
# Copyright (C) 2021, Kirill GPRB.
#
target_sources(voxelius PRIVATE
    "${CMAKE_CURRENT_LIST_DIR}/buffer.cc"
    "${CMAKE_CURRENT_LIST_DIR}/pipeline.cc"
    "${CMAKE_CURRENT_LIST_DIR}/shader.cc"
    "${CMAKE_CURRENT_LIST_DIR}/vertexarray.cc")
