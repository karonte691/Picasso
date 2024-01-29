#include <PEngine/File/FileManager.h>

#include <filesystem>
#include <fstream>

namespace Picasso::Engine::File
{
    FileManager *FileManager::Instance = nullptr;

    void FileManager::Init()
    {
        auto wPath = std::filesystem::current_path();
        m_CurrentWorkingPath = wPath.string();
    }

    PFile FileManager::Read(std::string filename)
    {
        std::filesystem::path filePath = std::filesystem::path(m_CurrentWorkingPath) / filename;
        std::ifstream fileStream(filePath, std::ios::in | std::ios::binary);

        if (!fileStream)
        {
            return {"", "", 0, ""};
        }

        std::stringstream buffer;
        buffer << fileStream.rdbuf();

        PFile file = this->_buildPFile(filename, filePath.string(), false, buffer.str());

        return file;
    }

    bool FileManager::Write(PFile file)
    {
        std::filesystem::path filePath = std::filesystem::path(file.absolutePath);
        std::ofstream fileStream(filePath, std::ios::out | std::ios::binary);

        if (!fileStream)
        {
            return false;
        }

        fileStream.write(file.content.c_str(), file.content.size());

        bool writeOpsRes = fileStream.good();

        fileStream.close();

        return writeOpsRes;
    }

    std::string FileManager::GetWorkingDirectory()
    {
        return m_CurrentWorkingPath;
    }

    PFile FileManager::_buildPFile(std::string filename, std::string absolutePath, bool isDirectory, std::string content)
    {
        PFile file = {
            filename,
            absolutePath,
            isDirectory,
            content};

        return file;
    }
}