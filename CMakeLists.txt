cmake_minimum_required(VERSION 3.6)

project(Engine)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/Thirdparty/cmake")

set(SDL2_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Thirdparty/SDL2")

find_package(SDL2 REQUIRED)

add_library(BuildSettings INTERFACE)
				   
set(PLATFORM_WIN32 FALSE CACHE INTERNAL "")
set(PLATFORM_LINUX FALSE CACHE INTERNAL "")
set(PLATFORM_MACOS FALSE CACHE INTERNAL "")
set(PLATFORM_ANDROID FALSE CACHE INTERNAL "")

if(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
    set(PLATFORM_WIN32 TRUE CACHE INTERNAL "Target platform: Win32")
	target_compile_definitions(BuildSettings INTERFACE PLATFORM_WIN32=1)
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    set(PLATFORM_LINUX TRUE CACHE INTERNAL "Target platform: Linux")
	target_compile_definitions(BuildSettings INTERFACE PLATFORM_LINUX=1)
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")
    set(PLATFORM_MACOS TRUE CACHE INTERNAL "Target platform: MacOS")
	target_compile_definitions(BuildSettings INTERFACE PLATFORM_MACOS=1)
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Android")
    set(PLATFORM_ANDROID TRUE CACHE INTERNAL "Target platform: Android")
	target_compile_definitions(BuildSettings INTERFACE PLATFORM_ANDROID=1)
else()
    message(FATAL_ERROR "Target platform: Unsupported!")
endif()

#add_subdirectory(NativeApp)
add_subdirectory(Thirdparty)
add_subdirectory(Platform)


# Use c++11
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11 -Wall -Werror")
set(CMAKE_BUILD_TYPE "Debug")

if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    target_compile_definitions(BuildSettings INTERFACE DEBUG=1)
endif()
