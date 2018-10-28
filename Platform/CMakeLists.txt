cmake_minimum_required(VERSION 3.6)

project(Platform)

if(PLATFORM_WIN32)

	set(SOURCE_FILES Windows/Win32Main.cpp Logger.h GameEngine.cpp GameEngine.h)

	include_directories(${SDL2_INCLUDE_DIR})

	add_executable(${APP_NAME} ${SOURCE_FILES})
	
	target_link_libraries(${APP_NAME} ${SDL2_LIBRARY} ${SDL2_SDLMAIN_LIBRARY} BuildSettings)
	
	add_custom_command(TARGET ${APP_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SDL2_RUNTIME_LIBRARY} $<TARGET_FILE_DIR:${APP_NAME}>)

elseif(PLATFORM_LINUX)

	set(SOURCE_FILES Linux/LinuxMain.cpp Logger.h GameEngine.cpp GameEngine.h)
	
	include_directories(${SDL2_INCLUDE_DIR})

	add_executable(${APP_NAME} ${SOURCE_FILES})

	target_link_libraries(${APP_NAME} ${SDL2_LIBRARY})

elseif(PLATFORM_ANDROID)

	set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -u ANativeActivity_onCreate")

	set(SOURCE_FILES Android/AndroidMain.cpp Android/AndroidApp.cpp Android/AndroidApp.h Logger.h GameEngine.cpp GameEngine.h)

	add_library(${APP_NAME} SHARED ${SOURCE_FILES})
    target_include_directories(${APP_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/Thirdparty/Android/NativeAppGlue/ ${CMAKE_SOURCE_DIR}/Thirdparty/Android/VulkanWrapper/)

	target_link_libraries(${APP_NAME} NativeAppGlue VulkanWrapper BuildSettings OpenSLES android log)

endif()

