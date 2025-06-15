#pragma once
#include "imetric.hpp"
#include <queue>
#include <functional>

template<typename T>
class Metric: public IMetric
{
private:
    std::string _name;
    std::function<T> _func;
    std::queue _values;
public:
    Metric(std::string name, std::function<T(const std::queue<t>&)> func);

    void add_value(T value);
    std::string aggregate() override;
};
