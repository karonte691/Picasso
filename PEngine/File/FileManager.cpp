#include <PEngine/File/FileManager.h>

#include <filesystem>

namespace Picasso::Engine::File
{
    FileManager *FileManager::Instance = nullptr;

    void FileManager::Init()
    {
        namespace fs = std::filesystem;

        auto wPath = fs::current_path();
        p_CurrentWorkingPath = wPath.c_str();
    }

    bool FileManager::Write(const char *filename, std::string data)
    {
        return true;
    }

    const char *FileManager::GetWorkingDirectory()
    {
        return p_CurrentWorkingPath;
    }

    PFile FileManager::_buildPFile(std::string filename, std::string absolutePath, bool isDirectory)
    {
        PFile file = {
            filename,
            absolutePath,
            isDirectory};

        return file;
    }
}