#pragma once

#include <cstdio>
#include <string>

namespace Monolith
{
    class FileReader
    {
    public:
        FileReader(const char* filePath);
        ~FileReader();

        bool IsFileOpen() const;
        bool IsAtEOF() const;
        u32 GetFileSize() const;

        void ReadFullFile(std::string& fileText) const;

    private:
        std::string m_FilePath;
        FILE* m_FileHandle;
    };
}