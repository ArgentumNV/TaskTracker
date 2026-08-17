cmake_minimum_required(VERSION 3.20)
project(TaskTracker VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(task_manager 
    src/main.cpp
    src/Task.cpp
    src/TaskManager.cpp
)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()


if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(task_manager PRIVATE DEBUG)
    message(STATUS "Building in Debug mode")
else()
    message(STATUS "Building in Release mode")
endif()


message(STATUS "Project: ${PROJECT_NAME} v${PROJECT_VERSION}")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "C++ Standard: ${CMAKE_CXX_STANDARD}")