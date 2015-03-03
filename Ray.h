#include "Vector.h"

class Ray {
  public:
    Coord start;
    Vector direction;
    int bouncesLeft;
    float tMin, tMax;
    Ray(Coord start, Vector direction, int bouncesLeft, float tMin, float tMax) :
    start(start), bouncesLeft(bouncesLeft), tMin(tMin), tMax(tMax)
    {
        direction = direction.normalize();
    }
};
