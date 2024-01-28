#pragma once

#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <string>

namespace Picasso::Engine::File
{
    struct PFile
    {
        std::string fileName;
        std::string absolutePath;
        bool isDirectory;
    };

    class FileManager
    {
    public:
        static FileManager *Instance;

        const char *GetWorkingDirectory();
        void Init();
        bool Write(const char *filename, std::string data);

    private:
        const char *p_CurrentWorkingPath;

        PFile _buildPFile(std::string filename, std::string absolutePath, bool isDirectory);
    };
}

#endif