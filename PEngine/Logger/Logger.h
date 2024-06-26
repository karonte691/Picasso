#pragma once

#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <stdarg.h>
#include <memory>
#include <iomanip>
#include <string>
#include <cstdarg>
#include <vector>
#include <cstdlib>
#include <chrono>

#include <PEngine/PBuild.h>
#include <PEngine/Logger/LogLevel.h>

namespace Picasso::Engine::Logger
{
    class Logger
    {
    public:
        template <typename... FuncArgs>
        static void Debug(const char *fmt_str, FuncArgs... args)
        {
            if (!PICASSO_DEBUG_ENABLE)
            {
                return;
            }

            _log(Levels::LogLevels::DEBUG, _formatStr(fmt_str, args...));
        }

        template <typename... FuncArgs>
        static void Info(const char *fmt_str, FuncArgs... args)
        {
            _log(Levels::LogLevels::INFO, _formatStr(fmt_str, args...));
        }

        template <typename... FuncArgs>
        static void Error(const char *fmt_str, FuncArgs... args)
        {
            _log(Levels::LogLevels::ERROR, _formatStr(fmt_str, args...));
        }

        template <typename... FuncArgs>
        static void Warn(const char *fmt_str, FuncArgs... args)
        {
            _log(Levels::LogLevels::WARN, _formatStr(fmt_str, args...));
        }

        template <typename... FuncArgs>
        static void Fatal(const char *fmt_str, FuncArgs... args)
        {
            _log(Levels::LogLevels::FATAL, _formatStr(fmt_str, args...));
        }

    private:
        static std::string _formatStr(const char *const zcFormat, ...)
        {

            // initialize use of the variable argument array
            va_list vaArgs;
            va_start(vaArgs, zcFormat);

            // reliably acquire the size
            // from a copy of the variable argument array
            // and a functionally reliable call to mock the formatting
            va_list vaArgsCopy;
            va_copy(vaArgsCopy, vaArgs);
            const int iLen = std::vsnprintf(nullptr, 0, zcFormat, vaArgsCopy);
            va_end(vaArgsCopy);

            // return a formatted string without risking memory mismanagement
            // and without assuming any compiler or platform specific behavior
            std::vector<char> zc(iLen + 1);
            std::vsnprintf(zc.data(), zc.size(), zcFormat, vaArgs);
            va_end(vaArgs);
            return std::string(zc.data(), iLen);
        }

        static void _log(Levels::LogLevels level, std::string str)
        {
            const char *levelName = Levels::ToString(level);

            auto now = std::chrono::system_clock::now();
            auto in_time_t = std::chrono::system_clock::to_time_t(now);

            auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;

            std::stringstream stringStream;
            stringStream << std::put_time(std::localtime(&in_time_t), "%Y-%m-%dT%H:%M:%S");
            stringStream << '.' << std::setfill('0') << std::setw(3) << milliseconds.count();

            std::string dateNow = stringStream.str();

            std::ostringstream oss;
            oss << "[" << dateNow << "][" << levelName << "] " << str;

            std::cout << oss.str() << "\n";
        }
    };

}

#endif