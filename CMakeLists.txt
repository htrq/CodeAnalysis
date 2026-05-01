cmake_minimum_required(VERSION 3.15.0)
project(fltkTest3 VERSION 0.1.0 LANGUAGES CXX)

add_executable(${PROJECT_NAME} 
${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
${CMAKE_CURRENT_SOURCE_DIR}/src/mainWindow.cpp
${CMAKE_CURRENT_SOURCE_DIR}/src/widgetData.cpp
${CMAKE_CURRENT_SOURCE_DIR}/src/linuxTerminal.cpp
${CMAKE_CURRENT_SOURCE_DIR}/src/tipTree.cpp
)

find_package(fltk CONFIG REQUIRED)

target_link_libraries(${PROJECT_NAME} PRIVATE
    fltk::fltk
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

get_target_property(inc fltk::fltk INTERFACE_INCLUDE_DIRECTORIES)
message(STATUS "FLTK includes = ${inc}")

