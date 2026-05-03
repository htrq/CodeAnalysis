cmake_minimum_required(VERSION 3.15.0)
project(fltkTest3 VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

add_executable(${PROJECT_NAME} 
${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
${CMAKE_CURRENT_SOURCE_DIR}/src/mainWindow.cpp
${CMAKE_CURRENT_SOURCE_DIR}/src/widgetData.cpp
${CMAKE_CURRENT_SOURCE_DIR}/src/linuxTerminal.cpp
${CMAKE_CURRENT_SOURCE_DIR}/src/tipTree.cpp
)

set(FLTK_DIR "${CMAKE_CURRENT_SOURCE_DIR}/third-party/fltk-1.4.5/")
find_package(FLTK CONFIG REQUIRED)

target_link_libraries(${PROJECT_NAME} PRIVATE
    fltk::fltk
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

