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
    Vector eval(float t);
    Ray(Coord start, Vector direction, int bouncesLeft, float tMin, float tMax) :
    start(start), bouncesLeft(bouncesLeft), tMin(tMin), tMax(tMax), direction(direction)
    {
        direction = direction.normalize();
    }
};

Vector Ray::eval(float t) {
    Vector e = Vector(start.x, start.y, start.z);
    return e + t*direction;
}

std::ostream& operator<< (std::ostream &out, Ray &ray)
{
    out << "tmin & tmax: " << ray.tMin << ", " << ray.tMax <<
        "direction: " << ray.direction << "\n";
    return out;
}

#endif
