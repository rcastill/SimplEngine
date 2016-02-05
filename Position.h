//
// Created by rcastill on 1/31/16.
//

#ifndef PROJECT_STRAT_VECTOR3_H
#define PROJECT_STRAT_VECTOR3_H

#include <cmath>

struct Position
{
    Position(float x, float y, float speed = 0, int r = 0);
    Position();

    float x;
    float y;
    double r;

    float speed;

    void lookTowards(int x, int y);

    void moveTowards(int x, int y, double timeStep = 1.0);
    void moveUp(double timeStep = 1.0);
    void moveLeft(double timeStep = 1.0);
    void moveDown(double timeStep = 1.0);
    void moveRight(double timeStep = 1.0);
};


#endif //PROJECT_STRAT_VECTOR3_H
