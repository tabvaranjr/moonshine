cmake_minimum_required(VERSION 3.8)
project(moonshine-tests)

find_package(Catch2 CONFIG REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS OFF)

set(SOURCE_FILES
    main.cpp
    )
add_executable(moonshine-tests ${SOURCE_FILES})
target_link_libraries(moonshine-tests PRIVATE Catch2::Catch2 ${CMAKE_DL_LIBS})
