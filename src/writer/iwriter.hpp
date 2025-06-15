#pragma once
#include <iostream>
#include <string>

class IWriter
{
private:
    std::string _filename;
public:
    IWriter();
    virtual void write(std::string log) = 0;
    virtual std::unique_ptr<IWriter> clone() = 0;
    virtual ~IWriter() = default;
};
