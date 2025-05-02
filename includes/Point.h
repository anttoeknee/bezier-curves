//
// Created by Anthony Armstrong on 02/05/2025.
//

#ifndef POINT_H
#define POINT_H
#include <string>

#endif //POINT_H

class Point {
public:
    Point(float originX, float originY, float width, float height, const std::string &name);

    void update(float newX, float newY);

    float getX() const;

    float getY() const;

    float getWidth() const;

    float getHeight() const;

    std::string getName() const;

private:
    float x, y;
    float width, height;
    std::string name;
};
