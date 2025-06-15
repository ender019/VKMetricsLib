#include "MetricsLib.hpp"

#include <iomanip>

void MetricsCollector::get_time(std::stringstream& out) {
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;
    out<<std::put_time(std::localtime(&time), "%Y-%m-%d %H:%M:%S")<<'.'<<ms.count();
}

void MetricsCollector::main_loop() {
    while (_active.load(std::memory_order_relaxed))
    {
        auto lbegin = std::chrono::steady_clock::now();

        std::stringstream out;
        get_time(out);
        out<<' ';
        for(auto& [name, metric]: _metrics) {
            out<<'\"'<<name<<"\" ";
            metric->aggregate(out);
            out<<' ';
        }
        _writer->write(out.str());

        auto lend = std::chrono::steady_clock::now();
        auto stime = lbegin + _delay - lend;
        if(stime > std::chrono::milliseconds(0)) 
            std::this_thread::sleep_for(stime);
    }
    
}

MetricsCollector::MetricsCollector(): _delay(1000), _active(0) {}

void MetricsCollector::start() {
    _active.store(1, std::memory_order_relaxed);
    _metric_thread = std::thread([this]() { this->main_loop(); });
}

void MetricsCollector::stop() {
    _active.store(0, std::memory_order_relaxed);
    if(!_metric_thread.joinable()) _metric_thread.join();
}

MetricsCollector& MetricsCollector::set_delay(long long delay) {
    _delay = std::chrono::milliseconds(delay);
    return *this;
}

MetricsCollector& MetricsCollector::set_writer(const IWriter& writer){
    _writer = writer.clone();
    return *this;
}