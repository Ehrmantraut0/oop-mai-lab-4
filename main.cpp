#include <iostream>
#include <memory>
#include "include/array.h"
#include "include/triangle.h"
#include "include/square.h"
#include "include/rectangle.h"

int main() {
    Array<std::shared_ptr<Figure<double>>> figures;
    std::string command;
    
    std::cout << "Commands: triangle, square, rectangle, delete <index>, exit" << std::endl;
    std::cin >> command;
    
    while (command != "exit") {
        if (command == "triangle" || command == "square" || command == "rectangle") {
            std::shared_ptr<Figure<double>> figure = nullptr;
            
            if (command == "triangle") {
                figure = std::make_shared<Triangle<double>>();
                std::cout << "Enter 3 points (x1 y1 x2 y2 x3 y3): ";
            }
            else if (command == "square") {
                figure = std::make_shared<Square<double>>();
                std::cout << "Enter 4 points (x1 y1 x2 y2 x3 y3 x4 y4): ";
            }
            else if (command == "rectangle") {
                figure = std::make_shared<Rectangle<double>>();
                std::cout << "Enter 4 points (x1 y1 x2 y2 x3 y3 x4 y4): ";
            }
            
            std::cin >> *figure;
            figures.push_back(figure);
            std::cout << "Added " << command << " as figure " << figures.size()-1 << std::endl;
        }
        else if (command == "delete") {
            int index;
            std::cin >> index;
            
            if (index >= 0 && index < (int)figures.size()) {
                figures.erase(index);
                std::cout << "Deleted figure " << index << std::endl;
            } else {
                std::cout << "Invalid index!" << std::endl;
            }
        }
        else {
            std::cout << "Unknown command" << std::endl;
        }
        std::cin >> command;
    }
    
    double totalArea = 0;
    std::cout << "\nFinal figures:" << std::endl;
    for (size_t i = 0; i < figures.size(); i++) {
        std::cout << "Figure " << i << ": " << *figures[i] << std::endl;
        Point<double> center = figures[i]->center();
        double area = static_cast<double>(*figures[i]);
        std::cout << "Center: (" << center.x << ", " << center.y << ")" << std::endl;
        std::cout << "Area: " << area << std::endl;
        totalArea += area;
    }
    
    std::cout << "Total area: " << totalArea << std::endl;
    
    Array<Square<int>> squares;
    squares.push_back(Square<int>(
        Point<int>{0, 0},
        Point<int>{5, 0},
        Point<int>{5, 5},
        Point<int>{0, 5}
    ));
    
    std::cout << "\nTesting Array with Square<int>:" << std::endl;
    std::cout << squares[0] << std::endl;
    std::cout << "Area: " << static_cast<double>(squares[0]) << std::endl;
    
    return 0;
}