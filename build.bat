@echo off

del /Q build

set BUILD_MOD=Release
echo %BUILD_MOD%

rem Конфигурация
cmake -B build -S . -DMETRICS_BUILD_EXAMPLES=ON

rem Сборка
cmake --build build --config %BUILD_MOD%

rem Установка
cmake --install build --config %BUILD_MOD%

rem Запуск примера
"./build/install/bin/metrics_example"