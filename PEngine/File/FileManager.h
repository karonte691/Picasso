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
        std::string content;
    };

    class FileManager
    {
    public:
        static FileManager *Instance;

        std::string GetWorkingDirectory();
        void Init();
        PFile Read(std::string file);
        bool Write(PFile file);

    private:
        std::string m_CurrentWorkingPath;

        PFile _buildPFile(std::string filename, std::string absolutePath, bool isDirectory, std::string content);
    };
}

#endif