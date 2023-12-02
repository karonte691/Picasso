#pragma once

#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <stdarg.h> 
#include <memory>
#include <string.h>

#include <PEngine/PBuild.h>

namespace Picasso::Logger
{
    enum LOG_LEVEL
    {
        DEBUG = 0,
        INFO = 1,
        WARN = 2,
        ERROR = 3,
        FATAL = 4,
    };

    class Logger
    {
    public:
        static void Debug(const char* str)
        {
            if(!PICASSO_DEBUG_ENABLE)
            {
                return;
            }

            Log(DEBUG, str);
        }
        static void FDebug(const std::string fmt_str, ...) 
        {
            if(!PICASSO_DEBUG_ENABLE)
            {
                return;
            }

            int final_n, n = ((int)fmt_str.size()) * 2; /* Reserve two times as much as the length of the fmt_str */
            std::unique_ptr<char[]> formatted;
            va_list ap;
            while(1) {
                formatted.reset(new char[n]); /* Wrap the plain char array into the unique_ptr */
                strcpy(&formatted[0], fmt_str.c_str());
                va_start(ap, fmt_str);
                final_n = vsnprintf(&formatted[0], n, fmt_str.c_str(), ap);
                va_end(ap);
                if (final_n < 0 || final_n >= n)
                    n += abs(final_n - n + 1);
                else
                    break;
            }   
            Log(DEBUG, formatted.get());
        }
        static void Info(const char* str)
        {
            Log(INFO, str);
        }
        static void Error(const char* str)
        {
            Log(ERROR, str);
        }
        static void Warn(const char* str)
        {
            Log(WARN, str);
        }
        static void Fatal(const char* str)
        {
            Log(FATAL, str);
        }
        static const char* formatStr(const std::string fmt_str, ...) {
            int final_n, n = ((int)fmt_str.size()) * 2; /* Reserve two times as much as the length of the fmt_str */
            std::unique_ptr<char[]> formatted;
            va_list ap;
            while(1) {
                formatted.reset(new char[n]); /* Wrap the plain char array into the unique_ptr */
                strcpy(&formatted[0], fmt_str.c_str());
                va_start(ap, fmt_str);
                final_n = vsnprintf(&formatted[0], n, fmt_str.c_str(), ap);
                va_end(ap);
                if (final_n < 0 || final_n >= n)
                    n += abs(final_n - n + 1);
                else
                    break;
        }   
        return formatted.get();
    }
    private:
        static void Log(LOG_LEVEL level, const char* str) 
        {
            const char* outputLevelStrings[5] = { "[DEBUG] ", "[INFO] ", "[WARN] ", "[ERROR] ", "[FATAL] "};

            std::cout << outputLevelStrings[level] << str << std::endl;
        }   
    };


}

#endif