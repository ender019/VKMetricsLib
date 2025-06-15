#pragma once
#include "metric.hpp"
#include "iwriter.hpp"
#include <vector>
#include <chrono>
#include <atomic>
#include <vector>
#include <map>
#include <thread>
#include <functional>

class MetricsCollector
{
private:
    std::map<std::string, std::shared_ptr<IMetric>> _metrics;
    std::chrono::milliseconds _delay;
    std::thread _metric_thread;
    std::unique_ptr<IWriter> _writer;
    std::atomic<bool> _active;

    void get_time(std::stringstream& out);
    void main_loop();

public:
    MetricsCollector();

    void start();
    void stop();

    MetricsCollector& set_delay(long long delay);
    MetricsCollector& set_writer(const IWriter& writer);

    template<typename T>
    std::function<void(const T&)> register_metric(std::string name, std::function<T(const std::vector<T>&)> func) {
        auto metric = std::make_shared<Metric<T>>(name, func);
        _metrics[name] = metric;
        return [metric](const T& value) { metric->add_value(value); };
    }

    ~MetricsCollector() = default;
};