#pragma once
#include "figure.h"
#include "point.h"
#include <memory>
#include <iostream>
#include <cmath>


template <Scalar T>
class Triangle : public Figure<T> {
private:
    std::unique_ptr<Point<T>> vertices[3];

    void read(std::istream& is) override {
        for(int i = 0; i < 3; i++) {
            is >> vertices[i]->x >> vertices[i]->y;
        }
    }

    void print(std::ostream& os) const override {
        os << "Triangle: ";
        for(int i = 0; i < 3; i++) {
            os << "(" << vertices[i]->x << "," << vertices[i]->y << ") ";
        }
    }

    bool equal(const Figure<T>& other) const override {
        const Triangle<T>* o = dynamic_cast<const Triangle<T>*>(&other);
        if(!o) return false;

        for(int i = 0; i < 3; i++) {
            if(vertices[i]->x != o->vertices[i]->x || vertices[i]->y != o->vertices[i]->y)
                return false;
        }
        return true;
    }

public:
    Triangle() {
        for(int i = 0; i < 3; i++) {
            vertices[i] = std::make_unique<Point<T>>(0, 0);
        }
    }

    Triangle(const Point<T>& p1, const Point<T>& p2, const Point<T>& p3) {
        vertices[0] = std::make_unique<Point<T>>(p1);
        vertices[1] = std::make_unique<Point<T>>(p2);
        vertices[2] = std::make_unique<Point<T>>(p3);
    }

    Triangle(std::unique_ptr<Point<T>> p1,
             std::unique_ptr<Point<T>> p2,
             std::unique_ptr<Point<T>> p3) {
        vertices[0] = std::move(p1);
        vertices[1] = std::move(p2);
        vertices[2] = std::move(p3);
    }

    Triangle(const Triangle& other) {
        for(int i = 0; i < 3; i++) {
            vertices[i] = std::make_unique<Point<T>>(*other.vertices[i]);
        }
    }

    Triangle& operator=(const Triangle& other) {
        if(this != &other) {
            for(int i = 0; i < 3; i++) {
                vertices[i] = std::make_unique<Point<T>>(*other.vertices[i]);
            }
        }
        return *this;
    }

    Triangle(Triangle&& other) noexcept {
        for(int i = 0; i < 3; i++) {
            vertices[i] = std::move(other.vertices[i]);
        }
    }

    Triangle& operator=(Triangle&& other) noexcept {
        if(this != &other) {
            for(int i = 0; i < 3; i++) {
                vertices[i] = std::move(other.vertices[i]);
            }
        }
        return *this;
    }

    Point<T> center() const override {
        T x = (vertices[0]->x + vertices[1]->x + vertices[2]->x) / 3;
        T y = (vertices[0]->y + vertices[1]->y + vertices[2]->y) / 3;
        return Point<T>{x, y};
    }

    operator double() const override {
        double area = std::abs(
            (vertices[0]->x * (vertices[1]->y - vertices[2]->y) +
             vertices[1]->x * (vertices[2]->y - vertices[0]->y) +
             vertices[2]->x * (vertices[0]->y - vertices[1]->y)) / 2.0
        );
        return area;
    }
};