cmake_minimum_required(VERSION 3.15)

set(project "MetricsLib")
project(${project} VERSION 1.0.0 LANGUAGES CXX)

# Настройка стандарта C++ (требуется C++17)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Опции сборки
option(METRICS_BUILD_EXAMPLES "Build examples" ON)

# Настройка выходных директорий
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_BINARY_DIR}/install" CACHE PATH "Installation directory" FORCE)
endif()


# Создание библиотеки
add_library(${project})

# Исходные файлы библиотеки
target_sources(${project} PRIVATE
    src/MetricsLib.cpp
    src/file_writer.cpp
)

# Публичные заголовочные файлы
target_include_directories(${project} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# Заголовочные файлы для установки
set(HEADERS
    include/metrics/imetric.hpp
    include/metrics/metric.hpp
    include/MetricsLib.hpp
    include/writers/file_writer.hpp
)


# Установка библиотеки
install(TARGETS ${project}
    EXPORT metrics-targets
    FILE_SET HEADERS
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include
)

install(FILES ${HEADERS} DESTINATION include)

# Установка заголовочных файлов
install(DIRECTORY 
    include/metrics
    include/writers
    DESTINATION include
)

# Экспорт для CMake
install(EXPORT metrics-targets
    FILE metrics-config.cmake
    NAMESPACE metrics::
    DESTINATION lib/cmake/${project}
)

# Пример использования
if(METRICS_BUILD_EXAMPLES)
    add_executable(metrics_example examples/main.cpp)
    target_link_libraries(metrics_example ${project})
    set_target_properties(metrics_example PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
    )
    
    # Установка примера
    install(TARGETS metrics_example DESTINATION bin)
endif()