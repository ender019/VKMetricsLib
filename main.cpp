#include "MetricsLib.hpp"
#include "filewriter.hpp"


int main() {
    MetricsCollector collector;
    collector.set_writer(FileWriter("metrics.log"));
    collector.set_delay(1000);
    
    // Регистрация метрики CPU (среднее значение)
    auto add_cpu_metric = collector.register_metric<double>("CPU", 
        [](const std::vector<double>& values) {
            if (values.empty()) return 0.0;
            double sum = 0.0;
            for (double v : values) sum += v;
            return sum / values.size();
        });
    
    // Регистрация метрики HTTP запросов (количество)
    auto add_http_metric = collector.register_metric<int>("HTTP requests RPS",
        [](const std::vector<int>& values) {
            return static_cast<int>(values.size());
        });
    
    // Запуск записи в файл каждую секунду
    collector.start();
    
    // Имитация работы системы

    auto load_test = [&](int kol = 50, int delay = 100) {
        for (int i = 0; i < kol; ++i) {
            add_cpu_metric(0.5 + i * 0.2); // Пример значения CPU
            add_http_metric(i * 10);        // Пример количества запросов
            std::this_thread::sleep_for(std::chrono::milliseconds(delay));
        }
    };

    load_test();

    return 0;
}