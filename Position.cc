#include "Position.h"

#define DEG(x) x * 180 * M_1_PI
#define RAD(x) x * M_PI / 180

Position::Position(float x, float y, double r) :
    x(x),
    y(y),
    r(r)
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
    r = 180 - DEG(atan2f(x - this->x, y - this->y));
}

void Position::moveForward(double timeStep)
{
    float dy = (float) (sin(M_PI_2 - RAD(r)) * speed);
    float dx = (float) (cos(M_PI_2 - RAD(r)) * speed);

    x += dx * timeStep;
    y -= dy * timeStep;
}
