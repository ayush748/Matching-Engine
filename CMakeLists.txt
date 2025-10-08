cmake_minimum_required(VERSION 3.20)
project(MatchingEnginePython)

set(CMAKE_CXX_STANDARD 17)

# Find pybind11
find_package(pybind11 REQUIRED)

# Source files
set(SOURCES
    src/matching_engine.cpp
    src/order_book.cpp
    src/order.cpp
    src/trade.cpp
    python_binding.cpp
)

pybind11_add_module(matching_engine ${SOURCES})
