#
# CMakeLists.txt
# Created: 2021-01-19, 22:20:56.
# Copyright (C) 2021, Kirill GPRB.
#
cmake_minimum_required(VERSION 3.10)
project(shaders VERSION 1.3.3.7 LANGUAGES NONE)

find_program(GLSLC NAMES "glslc.exe" "glslc" REQUIRED)

file(GLOB VERT_SRCS "${CMAKE_CURRENT_LIST_DIR}/src/*.vert")
file(GLOB FRAG_SRCS "${CMAKE_CURRENT_LIST_DIR}/src/*.frag")
set(GLSL_SRCS ${VERT_SRCS} ${FRAG_SRCS})

foreach(GLSL_SRC ${GLSL_SRCS})
    get_filename_component(FILENAME "${GLSL_SRC}" NAME)
    set(GLSL_SPV "${CMAKE_CURRENT_LIST_DIR}/${FILENAME}.spv")
    add_custom_command(
        OUTPUT "${GLSL_SPV}"
        COMMAND "${GLSLC}" "--target-env=opengl4.5" "-o" "${GLSL_SPV}" "${GLSL_SRC}"
        DEPENDS "${GLSL_SRCS}"
    )
    list(APPEND GLSL_SPVS "${GLSL_SPV}")
endforeach(GLSL_SRC)

add_custom_target(shaders ALL DEPENDS "${GLSL_SPVS}")
