#ifndef SPHERE_H
#define SPHERE_H

#include "Coord.h"
#include "Shape.h"
#include "Transform.h"

class Sphere: public Shape {
  public:
    Matrix matrixTransform;
    Sphere () {}
    Sphere(Coord center, float r, Material material) :
        center(center),
        r(r),
        matrixTransform(transMatrix)
        {
          this->setMaterial(material);
          matrixTransform = transMatrix;
        }
    Sphere(Coord center, float r) :
        center(center),
        r(r)
        { 
            matrixTransform = transMatrix;
        }
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
