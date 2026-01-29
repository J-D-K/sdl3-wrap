cmake_minimum_required(VERSION 3.30)

project(GBTiler)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SDL3 REQUIRED CONFIG REQUIRED COMPONENTS SDL3-shared)
find_package(Freetype REQUIRED)

add_executable(${PROJECT_NAME})

set(MAIN_SOURCES
    source/GBTiler.cpp
    source/main.cpp)

set(UI_SOURCES
    source/ui/MenuBar.cpp
    source/ui/Menu.cpp
    source/ui/MenuOption.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE include ../lib/include)

target_compile_options(${PROJECT_NAME} PRIVATE -O2)
target_sources(${PROJECT_NAME} PRIVATE ${MAIN_SOURCES} ${UI_SOURCES})

target_link_options(${PROJECT_NAME} PRIVATE -s)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3 Freetype::Freetype sdl3wrapper)