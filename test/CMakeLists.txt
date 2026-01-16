cmake_minimum_required(VERSION 3.30)

project("sdl3wrappertest")

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SDL3 REQUIRED CONFIG REQUIRED COMPONENTS SDL3-shared)

set(SOURCE_FILES
    source/Controllable.cpp
    source/main.cpp
    source/Object.cpp
    source/TestGame.cpp)

add_executable(${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} PRIVATE include ../lib/include)
target_sources(${PROJECT_NAME} PRIVATE ${SOURCE_FILES})
target_link_options(${PROJECT_NAME} PRIVATE -s)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3 sdl3wrapper -lSDL3_image)