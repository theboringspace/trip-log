cmake_minimum_required(VERSION 3.21)
project(trip-log LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

qt_add_executable(trip-log
    src/main.cpp)

target_link_libraries(trip-log PRIVATE Qt6::Widgets)