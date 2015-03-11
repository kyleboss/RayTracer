#ifndef HITRECORD_H
#define HITRECORD_H

#include "Coord.h"
#include "Vector.h"

class HitRecord {
  public:
  	float t;
    Coord intersection;
    Vector normal;
    Ray(float t, Coord intersection, Vector normal) :
    t(t), intersection(intersection), normal(normal)
    {}
};

std::ostream& operator<< (std::ostream &out, HitRecords &rec)
{
    out << "Hit record at t = " << rec.t << ", coord " << ray.intersection <<
        "normal: " << ray.normal << "\n";
    return out;
}

#endif
