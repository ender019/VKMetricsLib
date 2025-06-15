#pragma once
#include "src/metric/imetric.hpp"
#include "src/writer/iwriter.hpp"
#include <vector>
#include <chrono>
#include <atomic>
#include <queue>
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
    std::atomic<bool> active;

    std::string get_time();
public:
    MetricsCollector();

    void start();
    void stop();

    MetricsCollector set_delay(long long delay);
    MetricsCollector set_writer(IWriter* writer);

    template<typename T>
    MetricsCollector register_metric(std::string name, std::function<T(const std::queue<T>&)> func);

    ~MetricsCollector();
};