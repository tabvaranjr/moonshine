cmake_minimum_required(VERSION 3.8)
project(moonshine-tests)

find_package(Catch2 CONFIG REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(../src)

set(SOURCE_FILES
    main.cpp
    SandboxTest.cpp
    )

add_executable(moonshine-tests ${SOURCE_FILES})
target_link_libraries(moonshine-tests PRIVATE moonshine Catch2::Catch2 ${CMAKE_DL_LIBS})
