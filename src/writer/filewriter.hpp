#pragma once
#include "iwriter.hpp"

class FileWriter: public IWriter
{
private:
    std::string _filename;
public:
    FileWriter();
    void write(std::string log) override;
    std::unique_ptr<IWriter> clone() override;
};