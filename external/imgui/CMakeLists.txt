#
# CMakeLists.txt
# Created: 2021-03-05, 17:28:06.
# Copyright (C) 2021, Kirill GPRB.
#
cmake_minimum_required(VERSION 3.10)
project(imgui VERSION 1.81 LANGUAGES CXX)
add_library(imgui INTERFACE)
target_compile_definitions(imgui INTERFACE IMGUI_IMPL_OPENGL_LOADER_GLAD=1)
target_include_directories(imgui INTERFACE "${CMAKE_CURRENT_LIST_DIR}")
target_sources(imgui INTERFACE
    "${CMAKE_CURRENT_LIST_DIR}/imgui_draw.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/imgui_impl_glfw.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/imgui_impl_opengl3.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/imgui_stdlib.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/imgui_tables.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/imgui_widgets.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/imgui.cpp")
