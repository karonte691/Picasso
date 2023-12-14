#pragma once

#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <stdarg.h>
#include <memory>
#include <string>
#include <cstdarg>
#include <vector>
#include <cstdlib>

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
            std::string srt = std::string(fmt_str);

            _log(Levels::LogLevels::INFO, _formatStr(fmt_str, args...));
        }

        template <typename... FuncArgs>
        static void Error(const char *fmt_str, FuncArgs... args)
        {

            std::string srt = std::string(fmt_str);

            _log(Levels::LogLevels::ERROR, _formatStr(fmt_str, args...));
        }

        template <typename... FuncArgs>
        static void Warn(const char *fmt_str, FuncArgs... args)
        {
            std::string srt = std::string(fmt_str);

            _log(Levels::LogLevels::WARN, _formatStr(fmt_str, args...));
        }

        template <typename... FuncArgs>
        static void Fatal(const char *fmt_str, FuncArgs... args)
        {

            std::string srt = std::string(fmt_str);

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

            if (sizeof(vaArgs) == 0)
            {
                return std::string(zcFormat);
            }

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

            int size = snprintf(nullptr, 0, "[%s] %s", levelName, str.c_str());
            char *sBuffer = (char *)malloc(size + 1);
            sprintf(sBuffer, "[%s] %s", levelName, str.c_str());

            std::cout << sBuffer << str << std::endl;
        }
    };

}

#endif