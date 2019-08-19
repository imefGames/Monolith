#include <precomp.h>
#include <core\io\filereader.h>

#include <iostream>
#include <fstream>

namespace Monolith
{
    FileReader::FileReader(const char* filePath)
        : m_FilePath{ filePath }
    {
        fopen_s(&m_FileHandle, filePath, "rb");
    }

    FileReader::~FileReader()
    {
        if (IsFileOpen())
        {
            fclose(m_FileHandle);
        }
    }

    bool FileReader::IsFileOpen() const
    {
        return m_FileHandle != nullptr;
    }

    bool FileReader::IsAtEOF() const
    {
        return feof(m_FileHandle);
    }

    u32 FileReader::GetFileSize() const
    {
        u32 fileSize = 0;
        if (IsFileOpen())
        {
            u32 fileCurrentPosition = ftell(m_FileHandle);
            fseek(m_FileHandle, 0, SEEK_END);
            fileSize = ftell(m_FileHandle);
            fseek(m_FileHandle, fileCurrentPosition, SEEK_SET);
        }
        return fileSize;
    }

    void FileReader::ReadFullFile(std::string &fileText) const
    {
        if (IsFileOpen())
        {
            u32 fileSize = GetFileSize();
            fileText.resize(fileSize);
            fread_s(&fileText[0], fileSize, sizeof(char), fileSize, m_FileHandle);
        }
    }
}