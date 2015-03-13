#ifndef HITRECORD_H
#define HITRECORD_H

#include "Coord.h"
#include "Vector.h"

class HitRecord {
  public:
    bool isHit;
  	float t;
    Coord intersection;
    Vector normal;
    Sphere sphere;
    Triangle triangle;
    HitRecord(float t, Vector normal) : t(t), normal(normal), isHit(1) {}
    HitRecord(float t, Coord intersection, Vector normal, Sphere sphere) :
    t(t), intersection(intersection), normal(normal), isHit(1), sphere(sphere) {}
    HitRecord(float t, Coord intersection, Vector normal, Triangle triangle) :
    t(t), intersection(intersection), normal(normal), isHit(1), triangle(triangle)
    {}
    HitRecord(bool isHit) : isHit(0) {}
};

std::ostream& operator<< (std::ostream &out, HitRecord &rec)
{
    out << "Hit record at t = " << rec.t <<
        ", normal: " << rec.normal << "\n";
    return out;
}

#endif
