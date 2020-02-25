cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(qt_crashpad_test)

# CMake Policy
cmake_policy (SET CMP0020 NEW)

# Version
set(QTCRASHPADTEST_MAJOR_VERSION 0)
set(QTCRASHPADTEST_MINOR_VERSION 2)
set(QTCRASHPADTEST_PATCH_VERSION 0)
set(QTCRASHPADTEST_VERSION ${QTCRASHPADTEST_MAJOR_VERSION}.${QTCRASHPADTEST_MINOR_VERSION}.${QTCRASHPADTEST_PATCH_VERSION})
message(STATUS "${PROJECT_NAME} version ${QTCRASHPADTEST_VERSION}")
string(TIMESTAMP TODAY "%Y-%m-%d")
message(STATUS "Today: ${TODAY}")

if (UNIX)
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
else()
  include_directories("C:/crashpad/crashpad")
  include_directories("C:/crashpad/crashpad/third_party/mini_chromium/mini_chromium")
  link_directories("C:/crashpad/crashpad/out/Default/obj/client")
  link_directories("C:/crashpad/crashpad/out/Default/obj/third_party/mini_chromium/mini_chromium/base/")
  #link_directories("C:/crashpad/crashpad/out/Default/obj/third_party/gtest")
  #link_directories("C:/crashpad/crashpad/out/Default/obj/minidump")
  #link_directories("C:/crashpad/crashpad/out/Default/obj/snapshot")
  #link_directories("C:/crashpad/crashpad/out/Default/obj/handler")
  link_directories("C:/crashpad/crashpad/out/Default/obj/util")
  #link_directories("C:/crashpad/crashpad/out/Default/obj/compat")
  #link_directories("C:/crashpad/crashpad/out/Default/obj/test")
endif()

# Compile using c++ 2011
if (UNIX)
  add_compile_options(-std=c++11)
  add_compile_options(-Wall -Wextra)
  add_compile_options(-Wl,--no-as-needed)
else()
  add_compile_options(/MT)
endif()

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
add_subdirectory(installer)

#Configure files
set(ApplicationsDirX64 "@ApplicationsDirX64@")
configure_file("${PROJECT_SOURCE_DIR}/installer/config/config.xml.in"
               "${PROJECT_SOURCE_DIR}/installer/config/config.xml")
configure_file("${PROJECT_SOURCE_DIR}/installer/packages/qt_crashpad_test/meta/package.xml.in"
               "${PROJECT_SOURCE_DIR}/installer/packages/qt_crashpad_test/meta/package.xml" @ONLY)
if (WIN32)
  configure_file("${PROJECT_SOURCE_DIR}/third_party/crashpad/crashpad_handler.exe"
                 "${PROJECT_SOURCE_DIR}/installer/packages/qt_crashpad_test/data/bin/crashpad_handler.exe" COPYONLY)
  configure_file("${PROJECT_SOURCE_DIR}/third_party/windows/VC_redist.x64.exe"
                 "${PROJECT_SOURCE_DIR}/installer/packages/qt_crashpad_test/data/VC_redist.x64.exe" COPYONLY)
else()
  configure_file("${PROJECT_SOURCE_DIR}/third_party/crashpad/crashpad_handler"
                 "${PROJECT_SOURCE_DIR}/installer/packages/qt_crashpad_test/data/bin/crashpad_handler" COPYONLY)
endif()

