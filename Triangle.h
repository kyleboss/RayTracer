#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Coord.h"
#include "Shape.h"

class Triangle: public Shape {
  public:
    Triangle(Coord point1, Coord point2, Coord point3, Material material) :
        point1(point1),
        point2(point2),
        point3(point3)
        {
            this->setMaterial(material);
        }
    Triangle(Coord point1, Coord point2, Coord point3) :
        point1(point1),
        point2(point2),
        point3(point3)
        {}
    Coord point1;
    Coord point2;
    Coord point3;
};

std::ostream& operator<< (std::ostream &out, Triangle &triangle)
{
    out << "Triangle: (" << triangle.point1 << ", " <<
        triangle.point2 << ", " <<
        triangle.point3 << ")\n";
    return out;
}

#endif
