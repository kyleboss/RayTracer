#ifndef RAY_H
#define RAY_H

#include "Coord.h"
#include "Vector.h"

class Ray {
  public:
    Coord start;
    Vector direction;
    int bouncesLeft;
    float tMin, tMax;
    Ray(Coord start, float x, float y, float z, int bouncesLeft, float tMin, float tMax) :
    start(start), bouncesLeft(bouncesLeft), tMin(tMin), tMax(tMax), direction(x, y, z)
    {
        direction = direction.normalize();
    }
};

#endif
