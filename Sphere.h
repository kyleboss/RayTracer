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
    virtual std::basic_ostream<char, std::__1::char_traits<char> > print() {
        std::cout << this;
    }
};

std::ostream& operator<< (std::ostream &out, Sphere &sphere)
{
    out << "Sphere: (" << sphere.center << ") , r = " << sphere.r << "\n" <<
        "Material: " << sphere.material << "\n";
    return out;
}

#endif
