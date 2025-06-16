#pragma once
#include "iwriter.hpp"
#include <fstream>

namespace metrics
{
    class FileWriter: public IWriter
    {
    private:
        std::string _filename;
        std::ofstream _file;
    public:
        FileWriter(const std::string& filename);
        
        FileWriter(const FileWriter&) = delete;
        FileWriter& operator=(const FileWriter&) = delete;
        
        FileWriter(FileWriter&&) = default;
        FileWriter& operator=(FileWriter&&) = default;

        void write(const std::string& log) override;
        std::unique_ptr<IWriter> clone() const override;

        ~FileWriter() override;
    };
}