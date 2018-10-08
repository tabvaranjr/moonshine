cmake_minimum_required(VERSION 3.8)
project(moonshine-env)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(fmt CONFIG REQUIRED)
add_definitions("-DFMT_HEADER_ONLY")

find_package(spdlog CONFIG REQUIRED)

include_directories(../src)

set(SOURCE_FILES
    main.cpp)

add_executable(moonshine-env ${SOURCE_FILES})
target_link_libraries(moonshine-env PRIVATE moonshine spdlog::spdlog ${CMAKE_DL_LIBS})
