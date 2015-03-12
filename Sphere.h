#ifndef SPHERE_H
#define SPHERE_H

#include "Coord.h"
#include "Shape.h"

class Sphere: public Shape {
  public:
    Sphere () {}
    Sphere(Coord center, float r, Material material) :
        center(center),
        r(r)
        {
          this->setMaterial(material);
        }
    Sphere(Coord center, float r) :
        center(center),
        r(r)
        { }
    Coord center;
    float r;
    void print(std::ostream &out) {
      out << "Sphere: (" << this->center << ") , r = " << this->r << "\n" <<
        "Material: " << this->material << "\n";
    }
};

std::ostream& operator<< (std::ostream &out, Sphere &sphere)
{
    sphere.print(out);
    return out;
}

#endif
