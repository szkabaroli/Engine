cmake_minimum_required(VERSION 3.6)

# Build native app glue files
if(PLATFORM_ANDROID)
    set(NATIVE_APP_GLUE_SRC Android/NativeAppGlue/android_native_app_glue.c)
    set(NATIVE_APP_GLUE_INCLUDE Android/NativeAppGlue/)
    add_library(NativeAppGlue STATIC ${NATIVE_APP_GLUE_SRC})

    set(VULKAN_WRAPPER_SRC Android/VulkanWrapper/vulkan_wrapper.cpp)
    set(VULKAN_WRAPPER_INCLUDE Android/VulkanWrapper/)
    add_library(VulkanWrapper STATIC ${VULKAN_WRAPPER_SRC})
endif()