cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(qt_crashpad_test)

include_directories("/home/apalomer/libraries/crashpad/crashpad")
include_directories("/home/apalomer/libraries/crashpad/crashpad/third_party/mini_chromium/mini_chromium")
link_directories("/home/apalomer/libraries/crashpad/crashpad/out/Default/obj/client")
link_directories("/home/apalomer/libraries/crashpad/crashpad/out/Default/obj/third_party/mini_chromium/mini_chromium/base/")
link_directories("/home/apalomer/libraries/crashpad/crashpad/out/Default/obj/third_party/gtest")
link_directories("/home/apalomer/libraries/crashpad/crashpad/out/Default/obj/minidump")
link_directories("/home/apalomer/libraries/crashpad/crashpad/out/Default/obj/snapshot")
link_directories("/home/apalomer/libraries/crashpad/crashpad/out/Default/obj/handler")
link_directories("/home/apalomer/libraries/crashpad/crashpad/out/Default/obj/util")
link_directories("/home/apalomer/libraries/crashpad/crashpad/out/Default/obj/compat")
link_directories("/home/apalomer/libraries/crashpad/crashpad/out/Default/obj/test")

# Compile using c++ 2011
add_compile_options(-std=c++11)
add_compile_options(-Wall -Wextra)

# Set output folder
set(CMAKE_BIN "${CMAKE_SOURCE_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BIN})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BIN})

# Include Qt
find_package(Qt5 REQUIRED COMPONENTS Core Widgets)

# Add bin and build dir to include
set(CMAKE_INCLUDE_CURRENT_DIR ON)
include_directories(${CMAKE_SOURCE_DIR}/src)

# Autoporcess files
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Add code
add_subdirectory(src)
