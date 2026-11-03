cmake_minimum_required(VERSION 3.25)

project(UINCampus VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)

add_library(
    uincampus_core
    src/version.cpp
)

target_include_directories(
    uincampus_core
    PUBLIC include
)

add_executable(
    uin-campus
    app/main.cpp
)

target_link_libraries(
    uin-campus
    PRIVATE uincampus_core
)