cmake_minimum_required(VERSION 3.8)
project(moonshine)

add_subdirectory(env)
add_subdirectory(tests)

#
# Modules
#

# Set up the generated GLAD bindings
set(GLAD_DIR ${CMAKE_CURRENT_SOURCE_DIR}/external/glad)
set(GLAD_INCLUDE_DIR ${GLAD_DIR}/include)
set(GLAD_SRC ${GLAD_INCLUDE_DIR}/glad/glad.h ${GLAD_DIR}/src/glad.c)
include_directories(${GLAD_INCLUDE_DIR})

set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)

find_package(glfw3 CONFIG REQUIRED)

find_package(fmt CONFIG REQUIRED)
add_definitions("-DFMT_HEADER_ONLY")

find_package(spdlog CONFIG REQUIRED)

find_package(imgui CONFIG REQUIRED)

#
# The interesting booze!
#
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS OFF)

set(SOURCE_FILES
    src/Sandbox.cpp
    src/Sandbox.h
    src/GL/Object.h
    src/GL/Shader.cpp
    src/GL/Shader.h
    src/GL/Program.cpp
    src/GL/Program.h
    src/GL/VertexArray.cpp
    src/GL/VertexArray.h
    src/GL/Buffer.cpp
    src/GL/Buffer.h
    src/Helpers.h
    src/TestObject.cpp
    src/TestObject.h
    src/GL/ForwardDeclarations.h
    src/Entity.h
    src/imgui_impl_opengl3.cpp
    src/imgui_impl_opengl3.h
    src/imgui_impl_glfw.cpp
    src/imgui_impl_glfw.h
    )
add_library(moonshine ${SOURCE_FILES} ${GLAD_SRC})
target_link_libraries(moonshine PRIVATE glfw OpenGL::GL spdlog::spdlog imgui::imgui ${CMAKE_DL_LIBS})
