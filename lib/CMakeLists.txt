cmake_minimum_required(VERSION 3.30)

project(sdl3wrapper)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SDL3 REQUIRED CONFIG REQUIRED COMPONENTS SDL3-shared)

set(SOURCE_FILES
    source/Input.cpp
    source/sdl3.cpp
    source/Texture.cpp)

set(LIBRARIES
    -lSDL3_image
    -lpng
    -ljpeg)

add_library(${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} PRIVATE include)
target_sources(${PROJECT_NAME} PRIVATE ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3)