cmake_minimum_required (VERSION 3.8)

project(multi_draw)

find_package(glfw3 3.3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

include_directories(${GLEW_INCLUDE_DIRS})
include_directories(${OPENGL_INCLUDE_DIR})

link_directories(${GLEW_LIBRARY_DIRS})

add_executable(multi_draw main.cpp)

target_link_libraries(multi_draw glfw
        ${GLEW_LIBRARIES}
        ${OPENGL_gl_LIBRARY}
        ${OPENGL_glu_LIBRARY})


