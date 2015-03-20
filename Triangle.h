#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Coord.h"
#include "Shape.h"
#include "Transform.h"

class Triangle: public Shape {
  public:
    Matrix matrixTransform;
    Triangle () {}
    Triangle(Coord point1, Coord point2, Coord point3, Material material) :
        point1(point1),
        point2(point2),
        point3(point3), 
        hasNormal(0)                               
        {
            this->setMaterial(material);
            matrixTransform = transMatrix;
        }
    Triangle(Coord point1, Coord point2, Coord point3) :
        point1(point1),
        point2(point2),
        point3(point3),
        hasNormal(0)                
        {
            matrixTransform = transMatrix;
        }
    Triangle(Coord point1, Coord point2, Coord point3, Vector vn1, Vector vn2, Vector vn3) :
        point1(point1),
        point2(point2),
        point3(point3),
        vn1(vn1),
        vn2(vn2),
        vn3(vn3),
        hasNormal(1)                
        {
            matrixTransform = transMatrix;
        }  
    Triangle(Coord point1, Coord point2, Coord point3, Vector vn1, Vector vn2, Vector vn3, Material material) :
        point1(point1),
        point2(point2),
        point3(point3),
        vn1(vn1),
        vn2(vn2),
        vn3(vn3),
        hasNormal(1)                
        {
            this->setMaterial(material);
            matrixTransform = transMatrix;
        }        
    Coord point1;
    Coord point2;
    Coord point3;
    Vector vn1;
    Vector vn2;
    Vector vn3;
    bool hasNormal;
    void print(std::ostream &out) {
        out << "Triangle: (" << this->point1 << ", " 
            << this->point2 << ", " << this->point3 << ")\n" <<
        "Material: " << this->material << "\n";
    }
};

std::ostream& operator<< (std::ostream &out, Triangle &triangle)
{
    triangle.print(out);
    return out;
}

#endif
