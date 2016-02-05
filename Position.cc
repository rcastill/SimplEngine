//
// Created by rcastill on 1/31/16.
//

#include "Position.h"

Position::Position(float x, float y, float speed, int r) :
    x(x),
    y(y),
    r(r),
    speed(speed)
{
}

Position::Position() :
        Position(0, 0, 0)
{
}

void Position::moveTowards(int x, int y, double timeStep)
{
    float dx = x - this->x;
    float dy = y - this->y;
    this->x += dx * speed * timeStep;
    this->y += dy * speed * timeStep;
}

void Position::moveUp(double timeStep)
{
    y -= speed * timeStep;
}

void Position::moveLeft(double timeStep)
{
    x -= speed * timeStep;
}

void Position::moveDown(double timeStep)
{
    y += speed * timeStep;
}

void Position::moveRight(double timeStep)
{
    x += speed * timeStep;
}

void Position::lookTowards(int x, int y)
{
    r = (atan2f(x - this->x, y - this->y) * 180) / -3.14159265359 + 180;
}
