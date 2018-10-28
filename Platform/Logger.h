#pragma once

#if defined(PLATFORM_WIN32) || defined(PLATFORM_LINUX)

    #include <iostream>
    #include <string>
    #include <stdarg.h>

    enum ELogLevel{
        LOG_LEVEL_DEBUG,
        LOG_LEVEL_INFO,
        LOG_LEVEL_WARN,
        LOG_LEVEL_ERROR
    };

    template <typename ... Args>
    void Print(ELogLevel level, const char* tag, const char* format, Args const& ... args) noexcept
    {
        std::string s;

        switch (level)
        {
            case LOG_LEVEL_DEBUG:
                s = "D/";
                std::fprintf(stdout, s.append(tag).append(" ").append(format).append("\n").c_str(), args ...);
                break;
            case LOG_LEVEL_INFO:
                s = "I/";
                std::fprintf(stdout, s.append(tag).append(" ").append(format).append("\n").c_str(), args ...);
                break;
            case LOG_LEVEL_WARN:
                s = "W/";
                std::fprintf(stdout, s.append(tag).append(" ").append(format).append("\n").c_str(), args ...);
                break;
            case LOG_LEVEL_ERROR:
                s = "E/";
                std::fprintf(stderr, s.append(tag).append(" ").append(format).append("\n").c_str(), args ...);
                break;
        }
    }

    #define  LOG_DEBUG(LogTag, ...) Print(LOG_LEVEL_DEBUG, LogTag, __VA_ARGS__);
    #define  LOG_INFO(LogTag, ...)  Print(LOG_LEVEL_INFO, LogTag, __VA_ARGS__);
    #define  LOG_WARN(LogTag, ...)  Print(LOG_LEVEL_WARN, LogTag, __VA_ARGS__);
    #define  LOG_ERROR(LogTag, ...) Print(LOG_LEVEL_ERROR, LogTag, __VA_ARGS__);

#elif defined(PLATFORM_ANDROID)
    #include <android/log.h>

    #define  LOG_DEBUG(LogTag, ...)  __android_log_print(ANDROID_LOG_DEBUG, LogTag, __VA_ARGS__);
    #define  LOG_INFO(LogTag, ...)  __android_log_print(ANDROID_LOG_INFO, LogTag, __VA_ARGS__);
    #define  LOG_WARN(LogTag, ...)  __android_log_print(ANDROID_LOG_WARN, LogTag, __VA_ARGS__);
    #define  LOG_ERROR(LogTag, ...)  __android_log_print(ANDROID_LOG_ERROR, LogTag, __VA_ARGS__);
#endif
