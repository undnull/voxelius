#
# CMakeLists.txt
# Created: 2021-01-16, 15:15:01.
# Copyright (C) 2021, Kirill GPRB.
#
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

if(POLICY CMP0079)
    cmake_policy(SET CMP0079 NEW)
endif()

add_subdirectory(glad)
target_link_libraries(voxelius glad)

add_subdirectory(glfw)
target_link_libraries(voxelius glfw)

add_subdirectory(glm)
target_link_libraries(voxelius glm)

add_subdirectory(imgui)
target_link_libraries(voxelius imgui)

add_subdirectory(json)
target_link_libraries(voxelius json)

add_subdirectory(stb)
target_link_libraries(voxelius stb)
