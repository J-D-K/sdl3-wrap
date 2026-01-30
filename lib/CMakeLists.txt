cmake_minimum_required(VERSION 3.30)

project(sdl3wrapper)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SDL3 REQUIRED CONFIG REQUIRED COMPONENTS SDL3-shared)
find_package(Freetype REQUIRED)

set(SOURCE_FILES
    source/Font.cpp
    source/Input.cpp
    source/Renderer.cpp
    source/Texture.cpp)

add_library(${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} PRIVATE include)
target_compile_options(${PROJECT_NAME} PRIVATE -O3)
target_sources(${PROJECT_NAME} PRIVATE ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3 Freetype::Freetype -lSDL3_image)