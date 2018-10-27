cmake_minimum_required(VERSION 3.6)

project(Platform)

if(PLATFORM_WIN32)

	set(SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/Windows/Win32Main.cpp)
	
	include_directories(${SDL2_INCLUDE_DIR})
	
	add_executable(NativeApp ${SOURCE_FILES})
	
	target_link_libraries(NativeApp ${SDL2_LIBRARY} ${SDL2_SDLMAIN_LIBRARY})
	
	add_custom_command(TARGET NativeApp POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SDL2_RUNTIME_LIBRARY} $<TARGET_FILE_DIR:NativeApp>)

elseif(PLATFORM_LINUX)

	set(SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/Linux/LinuxMain.cpp)
	
	include_directories(${SDL2_INCLUDE_DIR})

	add_executable(NativeApp ${SOURCE_FILES})

	target_link_libraries(NativeApp ${SDL2_LIBRARY})

elseif(PLATFORM_ANDROID)
	set(SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/Android/AndroidMain.cpp)
	add_library(NativeApp SHARED ${SOURCE_FILES})
endif()

