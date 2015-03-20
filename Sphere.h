#ifndef SPHERE_H
#define SPHERE_H

#include "Coord.h"
#include "Shape.h"
#include "Transform.h"

class Sphere: public Shape {
  public:
    Sphere () {}
    Sphere(Coord center, float r, Material material) :
        center(center),
        r(r)        {
        }
    Sphere(Coord center, float r, Material material, Matrix transMatrix2) :
        center(center),
        r(r),
        matrixTransform(transMatrix2)
        {
            this->setMaterial(material);
            this->matrixTransform = Matrix(transMatrix2);
        }
    Sphere(Coord center, float r) :
        center(center),
        r(r)
        { }
    Matrix matrixTransform;
    Coord center;
    float r;
    void print(std::ostream &out) {
      out << "Sphere: (" << this->center << ") , r = " << this->r << "\n" <<
        "Material: " << this->material << "matrix\n" << this->matrixTransform << "\n";
    }
};

std::ostream& operator<< (std::ostream &out, Sphere &sphere)
{
    sphere.print(out);
    return out;
}

#endif
