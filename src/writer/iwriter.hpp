#pragma once
#include <memory>
#include <string>

namespace metrics
{
    class IWriter
    {
    public:
        virtual void write(const std::string& log) = 0; // Метод записи метрик
        virtual std::unique_ptr<IWriter> clone() const = 0; // Метод создания ссылки на объект
        virtual ~IWriter() = default;
    };
}