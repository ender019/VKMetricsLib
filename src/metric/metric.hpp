#pragma once
#include "imetric.hpp"
#include <vector>
#include <functional>
#include <mutex>
#include <iostream>

namespace metrics
{
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

        void add_value(T value) {   // Добавление значения
            std::lock_guard<std::mutex> lock(_mutex);
            _values.push_back(value);
        }

        void aggregate(std::stringstream& out) override {   // Подсчет метрик
            std::vector<T> measures;
            {
                std::lock_guard<std::mutex> lock(_mutex);
                _values.swap(measures);
            }
            out<<_func(measures);
        }
    };
}