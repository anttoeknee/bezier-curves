
#include "../includes/Point.h"

Point::Point(float x, float y, float width, float height, const std::string& name)
    : x(x), y(y), width(width), height(height), name(name) {}

float Point::getX() const {
    return x;
}

float Point::getY() const {
    return y;
}

float Point::getWidth() const {
    return width;
}

float Point::getHeight() const {
    return height;
}

std::string Point::getName() const {
    return name;
}

void Point::update(float newX, float newY) {
    x = newX;
    y = newY;
}




