#pragma once
#include <string>

class IMetric
{
public:
    virtual std::string aggregate() = 0;
    virtual ~IMetric() = default;
};
