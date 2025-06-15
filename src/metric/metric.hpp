#pragma once
#include "imetric.hpp"
#include <vector>
#include <functional>
#include <mutex>

template<typename T>
class Metric: public IMetric
{
private:
    std::string _name;
    std::function<T(const std::vector<T>&)> _func;
    std::vector<T> _values;
    mutable std::mutex _mutex;
public:
    Metric(std::string name, std::function<T(const std::vector<T>&)> func):
        _name(name), _func(func) {}

    void add_value(T value) {
        std::lock_guard<std::mutex> lock(_mutex);
        _values.push_back(value);
    }

    void aggregate(std::stringstream& out) override {
        std::vector<T> measures;
        {
            std::lock_guard<std::mutex> lock(_mutex);
            _values.swap(measures);
            out<<_func(measures);
        }
    }
};
