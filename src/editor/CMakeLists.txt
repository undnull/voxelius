#
# CMakeLists.txt
# Created: 2021-03-05, 19:45:02.
# Copyright (C) 2021, Kirill GPRB.
#
target_sources(voxelius PRIVATE
    "${CMAKE_CURRENT_LIST_DIR}/editor.cc"
    "${CMAKE_CURRENT_LIST_DIR}/file_browser.cc"
    "${CMAKE_CURRENT_LIST_DIR}/logger_out.cc"
    "${CMAKE_CURRENT_LIST_DIR}/menu_bar.cc")
