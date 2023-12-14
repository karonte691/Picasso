#pragma once

#ifndef LOG_LEVEL
#define LOG_LEVEL

namespace Picasso::Engine::Logger::Levels
{
    enum class LogLevels
    {
        DEBUG = 0,
        INFO = 1,
        WARN = 2,
        ERROR = 3,
        FATAL = 4,
    };

    inline const char *ToString(LogLevels level)
    {
        switch (level)
        {
        case LogLevels::DEBUG:
            return "Debug";
        case LogLevels::INFO:
            return "Info";
        case LogLevels::WARN:
            return "Warn";
        case LogLevels::ERROR:
            return "Error";
        case LogLevels::FATAL:
            return "Fatal";
        default:
            return "[Unknown log level]";
        }
    }
}

#endif