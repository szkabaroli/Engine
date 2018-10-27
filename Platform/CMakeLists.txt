cmake_minimum_required(VERSION 3.6)

project(Platform)

if(PLATFORM_WIN32)

	set(SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/Windows/Win32Main.cpp)
	
	include_directories(${SDL2_INCLUDE_DIR})
	
	add_executable(Win32Exe ${SOURCE_FILES})
	
	target_link_libraries(Win32Exe ${SDL2_LIBRARY} ${SDL2_SDLMAIN_LIBRARY} winmm imm32 version )
	
	
	add_custom_command(TARGET Win32Exe POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SDL2_RUNTIME_LIBRARY} $<TARGET_FILE_DIR:Win32Exe>
                   COMMENT "Copying 'test' library to '${COPY_TO_PATH}'")
				   
elseif(PLATFORM_ANDROID)
	file(GLOB SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/Android/*.cpp)
	add_library(PlatformLib STATIC ${SOURCE_FILES})
endif()

