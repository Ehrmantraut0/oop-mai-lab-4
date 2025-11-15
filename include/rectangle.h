#pragma once
#include "figure.h"
#include "point.h"
#include <memory>
#include <iostream>
#include <cmath>

template <Scalar T>
class Rectangle : public Figure<T> {
private:
    std::unique_ptr<Point<T>> vertices[4];

    void read(std::istream& is) override {
        for(int i = 0; i < 4; i++) {
            is >> vertices[i]->x >> vertices[i]->y;
        }
    }

    void print(std::ostream& os) const override {
        os << "Rectangle: ";
        for(int i = 0; i < 4; i++) {
            os << "(" << vertices[i]->x << "," << vertices[i]->y << ") ";
        }
    }

    bool equal(const Figure<T>& other) const override {
        const Rectangle<T>* o = dynamic_cast<const Rectangle<T>*>(&other);
        if(!o) return false;

        for(int i = 0; i < 4; i++) {
            if(vertices[i]->x != o->vertices[i]->x || vertices[i]->y != o->vertices[i]->y)
                return false;
        }
        return true;
    }

public:
    Rectangle() {
        for(int i = 0; i < 4; i++) {
            vertices[i] = std::make_unique<Point<T>>(0, 0);
        }
    }

    Rectangle(const Point<T>& p1, const Point<T>& p2, const Point<T>& p3, const Point<T>& p4) {
        vertices[0] = std::make_unique<Point<T>>(p1);
        vertices[1] = std::make_unique<Point<T>>(p2);
        vertices[2] = std::make_unique<Point<T>>(p3);
        vertices[3] = std::make_unique<Point<T>>(p4);
    }

    Rectangle(std::unique_ptr<Point<T>> p1,
              std::unique_ptr<Point<T>> p2,
              std::unique_ptr<Point<T>> p3,
              std::unique_ptr<Point<T>> p4) {
        vertices[0] = std::move(p1);
        vertices[1] = std::move(p2);
        vertices[2] = std::move(p3);
        vertices[3] = std::move(p4);
    }

    Rectangle(const Rectangle& other) {
        for(int i = 0; i < 4; i++) {
            vertices[i] = std::make_unique<Point<T>>(*other.vertices[i]);
        }
    }

    Rectangle& operator=(const Rectangle& other) {
        if(this != &other) {
            for(int i = 0; i < 4; i++) {
                vertices[i] = std::make_unique<Point<T>>(*other.vertices[i]);
            }
        }
        return *this;
    }

    Rectangle(Rectangle&& other) noexcept {
        for(int i = 0; i < 4; i++) {
            vertices[i] = std::move(other.vertices[i]);
        }
    }

    Rectangle& operator=(Rectangle&& other) noexcept {
        if(this != &other) {
            for(int i = 0; i < 4; i++) {
                vertices[i] = std::move(other.vertices[i]);
            }
        }
        return *this;
    }

    Point<T> center() const override {
        T x = (vertices[0]->x + vertices[1]->x + vertices[2]->x + vertices[3]->x) / 4;
        T y = (vertices[0]->y + vertices[1]->y + vertices[2]->y + vertices[3]->y) / 4;
        return Point<T>{x, y};
    }

    operator double() const override {
        double width = std::sqrt(std::pow(vertices[1]->x - vertices[0]->x, 2) +
                                 std::pow(vertices[1]->y - vertices[0]->y, 2));
        double height = std::sqrt(std::pow(vertices[2]->x - vertices[1]->x, 2) +
                                  std::pow(vertices[2]->y - vertices[1]->y, 2));
        return width * height;
    }
};