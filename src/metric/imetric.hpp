#pragma once
#include <string>

namespace metrics
{
    class IMetric
    {
    public:
        virtual void aggregate(std::stringstream& out) = 0; // Подсчет метрик

        virtual ~IMetric() = default;
    };
}