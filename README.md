# Библиотека для сбора и записи метрик на C++
Этот проект предоставляет легковесную библиотеку на C++ для сбора, агрегации и записи метрик в файл. Библиотека разработана с учетом требований многопоточности и эффективности.

## Основные возможности
- Гибкая система метрик: Поддержка различных типов данных и агрегаторов

- Потокобезопасность: Безопасное использование из нескольких потоков

- Периодическая запись: Автоматическая запись метрик с заданным интервалом

- Эффективная агрегация: Минимизация блокировок при работе с данными

- Гибкий вывод: Форматированные записи с временными метками

## Использование
Регистрация метрик
```cpp
MetricsCollector collector;

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
```
Запуск периодической записи
```cpp
// Запуск записи в файл каждую секунду
metrics::MetricsCollector collector; // Создание объекта для учета метрик
collector.set_writer(metrics::FileWriter("metrics.log")); // Установка объекта записи
collector.set_delay(1000); // Установка интервала подсчета и записи

writer.start(); // Запуск мониторинга
```
Добавление значений метрик
```cpp
// В рабочем коде приложения
add_cpu_metric(0.75);    // Добавление значения CPU
add_http_metric(42);     // Добавление количества запросов
```
### Формат выходного файла
Каждая строка содержит временную метку и пары "имя метрики - значение":

```text
2025-06-16 19:19:50.571 "CPU" 5.50225 "HTTP requests RPS" 89 
2025-06-16 19:19:51.576 "CPU" 16.02 "HTTP requests RPS" 85 
2025-06-16 19:19:52.584 "CPU" 26.2906 "HTTP requests RPS" 85 
2025-06-16 19:19:53.596 "CPU" 35.8816 "HTTP requests RPS" 87 
2025-06-16 19:19:54.597 "CPU" 46.4301 "HTTP requests RPS" 83 
2025-06-16 19:19:55.604 "CPU" 60.3278 "HTTP requests RPS" 79 
2025-06-16 19:19:56.616 "CPU" 77.3306 "HTTP requests RPS" 72 
2025-06-16 19:19:57.624 "CPU" 88.936 "HTTP requests RPS" 50 
```

## Требования
- Компилятор с поддержкой C++17

- Стандартная библиотека C++

## Сборка
Проект может быть собран с помощью CMake:

```bash
build.bat
```

## Примеры метрик
- Средняя загрузка CPU
```cpp
auto cpu_metric = collector.register_metric<double>("CPU", 
    [](const std::vector<double>& values) {
        double sum = 0.0;
        for (double v : values) sum += v;
        return values.empty() ? 0.0 : sum / values.size();
    });
```
- Количество HTTP-запросов
```cpp
auto http_metric = collector.register_metric<int>("HTTP requests",
    [](const std::vector<int>& values) {
        return values.size();
    });
```
- Максимальное время ответа
```cpp
auto response_metric = collector.register_metric<double>("Max response time",
    [](const std::vector<double>& values) {
        if (values.empty()) return 0.0;
        double max = values[0];
        for (double v : values) if (v > max) max = v;
        return max;
    });
```

## Особенности реализации
- Потокобезопасность:

Каждая метрика защищена собственным мьютексом

Используется идиома swap для минимизации времени блокировки

- Эффективность:

Агрегация выполняется над локальной копией данных

Отсутствие блокировок при добавлении значений

- Гибкость:

Поддержка любых типов данных через шаблоны

Возможность использования пользовательских агрегаторов

## Дополнительная информация

- [Отладочный проект](https://github.com/ender019/VKMetricsLib/tree/dev) собранный как испоняемый файл.
- [Библиотека](https://github.com/ender019/VKMetricsLib/tree/restruct) собранный как испоняемый файл.
- Из-за сложностей с CMake не получилось собрать проект как библиотеку.
