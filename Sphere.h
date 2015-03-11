#ifndef SPHERE_H
#define SPHERE_H

#include "Coord.h"

class Sphere {
  public:
    Sphere(Coord center, float r,) :
        center(center),
        r(r)
        {}
    Coord center;
    float r;
};

std::ostream& operator<< (std::ostream &out, Sphere &sphere)
{
    out << "Sphere: (" << sphere.center << ") , r = " << sphere.r << "\n";
    return out;
}

#endif
