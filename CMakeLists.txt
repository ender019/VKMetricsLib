cmake_minimum_required(VERSION 3.26)

set(project "MetricsLib")
project(${project})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(SOURCE
    src/writer/filewriter.cpp
    MetricsLib.cpp
	main.cpp
)

set(HEADERS
    src/metric/imetric.hpp
    src/metric/metric.hpp
    src/writer/filewriter.hpp
    src/writer/iwriter.hpp
    MetricsLib.hpp
)

add_executable(${PROJECT_NAME} ${SOURCE} ${HEADERS})

target_include_directories(${PROJECT_NAME} PUBLIC src/metric)
target_include_directories(${PROJECT_NAME} PUBLIC src/writer)


configure_file(${CMAKE_CURRENT_SOURCE_DIR}/metrics.log ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)