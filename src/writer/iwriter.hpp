#pragma once
#include <memory>
#include <string>

class IWriter
{
public:
    virtual void write(const std::string& log) = 0;
    virtual std::unique_ptr<IWriter> clone() const = 0;
    virtual ~IWriter() = default;
};
