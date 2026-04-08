cmake_minimum_required(VERSION 3.15.0)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
project(fltkTest3 VERSION 0.1.0 LANGUAGES CXX)

add_executable(${PROJECT_NAME} 
${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
${CMAKE_CURRENT_SOURCE_DIR}/src/mainWindow.cpp
${CMAKE_CURRENT_SOURCE_DIR}/src/widgetData.cpp
${CMAKE_CURRENT_SOURCE_DIR}/src/linuxTerminal.cpp
)

find_package(FLTK CONFIG REQUIRED)

target_link_libraries(${PROJECT_NAME} PRIVATE fltk)
target_link_libraries(${PROJECT_NAME} PRIVATE vterm)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(${PROJECT_NAME} PRIVATE "cxx_std_23")


target_compile_options(${PROJECT_NAME} PRIVATE
    $<$<CONFIG:Debug>:-g -O0>
)