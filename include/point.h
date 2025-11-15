#pragma once
#include <concepts>

template<typename T>
concept Scalar = std::is_arithmetic_v<T>;

template <Scalar T>
struct Point {
    T x{};
    T y{};
    Point() = default;
    Point(T x_, T y_) : x(x_), y(y_) {}
};