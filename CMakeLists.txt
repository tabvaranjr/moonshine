cmake_minimum_required(VERSION 3.8)
project(moonshine)

#
# Modules
#
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

find_package(LibEpoxy REQUIRED)
include_directories(${LibEpoxy_INCLUDE_DIR})

if(USE_EXTERNAL_GLFW)
    message(STATUS "Using external GLFW")
    add_subdirectory(external/glfw)
else()
    find_package(GLFW REQUIRED)
endif()

if(USE_EXTERNAL_FMT)
    message(STATUS "Using external fmt")
    add_subdirectory(external/fmt)
else()
    find_package(Fmt REQUIRED)
endif()
add_definitions("-DFMT_HEADER_ONLY")

#
# The interesting booze!
#
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS OFF)

set(SOURCE_FILES src/main.cpp src/Sandbox.cpp src/Sandbox.h src/File.cpp src/File.h src/GL/Object.h src/GL/Shader.cpp src/GL/Shader.h src/GL/Program.cpp src/GL/Program.h src/GL/VertexArray.cpp src/GL/VertexArray.h src/GL/Buffer.cpp src/GL/Buffer.h src/Helpers.h src/TestObject.cpp src/TestObject.h src/GL/ForwardDeclarations.h)
add_executable(moonshine ${SOURCE_FILES})
target_link_libraries(moonshine ${GLFW_LIBRARIES} ${GLFW_LIBRARY} ${OPENGL_LIBRARIES} ${LibEpoxy_LIBRARIES})
