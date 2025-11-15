#pragma once
#include "point.h"
#include <iostream>

template <Scalar T>
class Figure {
public:
    virtual ~Figure() = default;
    virtual Point<T> center() const = 0;
    virtual operator double() const = 0;

private:
    virtual void read(std::istream& is) = 0;
    virtual void print(std::ostream& os) const = 0;
    virtual bool equal(const Figure<T>& other) const = 0;

    friend std::istream& operator>>(std::istream& is, Figure<T>& figure) {
        figure.read(is);
        return is;
    }

    friend std::ostream& operator<<(std::ostream& os, const Figure<T>& figure) {
        figure.print(os);
        return os;
    }

    friend bool operator==(const Figure<T>& f1, const Figure<T>& f2) {
        return f1.equal(f2);
    }
};