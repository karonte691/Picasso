/**
 * @file FileManager.cpp
 * @brief Implementation of the FileManager class.
 */

#include <PEngine/File/FileManager.h>

#include <filesystem>
#include <fstream>

namespace Picasso::Engine::File
{
    FileManager *FileManager::Instance = nullptr;

    /**
     * @brief Initializes the FileManager by setting the current working path.
     */
    void FileManager::Init()
    {
        auto wPath = std::filesystem::current_path();
        m_CurrentWorkingPath = wPath.string();
    }

    /**
     * @brief Reads a file and returns a PFile object containing the file's information.
     * @param filename The name of the file to read.
     * @return A PFile object representing the file.
     */
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

        fileStream.close();

        return file;
    }

    /**
     * @brief Writes a PFile object to a file.
     * @param file The PFile object to write.
     * @return True if the write operation was successful, false otherwise.
     */
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

    /**
     * @brief Gets the current working directory.
     * @return The current working directory.
     */
    std::string FileManager::GetWorkingDirectory()
    {
        return m_CurrentWorkingPath;
    }

    /**
     * @brief Builds a PFile object with the given parameters.
     * @param filename The name of the file.
     * @param absolutePath The absolute path of the file.
     * @param isDirectory True if the file is a directory, false otherwise.
     * @param content The content of the file.
     * @return A PFile object representing the file.
     */
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