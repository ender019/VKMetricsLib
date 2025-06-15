#pragma once
#include <string>

class IMetric
{
public:
    virtual void aggregate(std::stringstream& out) = 0;

    virtual ~IMetric() = default;
};
