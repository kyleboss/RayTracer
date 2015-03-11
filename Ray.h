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
    Ray(Coord start, Vector direction, int bouncesLeft, float tMin, float tMax) :
    start(start), bouncesLeft(bouncesLeft), tMin(tMin), tMax(tMax), direction(direction)
    {
        direction = direction.normalize();
    }
};

std::ostream& operator<< (std::ostream &out, Ray &ray)
{
    out << "tmin & tmax: " << ray.tMin << ", " << ray.tMax <<
        "direction: " << ray.direction << "\n";
    return out;
}

#endif
