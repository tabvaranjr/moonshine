cmake_minimum_required(VERSION 3.8)
project(moonshine)

#
# Options
#
option(USE_EXTERNAL_GLFW "Use the version of GLFW found in the 'external' directory" OFF)
option(USE_EXTERNAL_FMT "Use the version of FMT found in the 'external' directory" OFF)

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

set(SOURCE_FILES main.cpp)
add_executable(moonshine ${SOURCE_FILES})
target_link_libraries(moonshine ${GLFW_LIBRARIES} ${OPENGL_LIBRARIES} ${LibEpoxy_LIBRARIES})
