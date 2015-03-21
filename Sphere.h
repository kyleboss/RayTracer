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
            std::cout << "IMA SPHERE" << std::endl;
            this->setMaterial(material);
            this->preTransform = Matrix(transMatrix2);
            this->notInvertedTransform = preTransform.copy();
            this->matrixTransform = Matrix();
            MatrixInversion(this->preTransform.matrix, 4, this->matrixTransform.matrix);
            Vector p1;
            Vector p2;
            Vector p3;
            Vector p4;
            Vector p5;
            Vector p6;
            Vector p7;
            Vector p8;
            Vector ps[8] = {};
            ps[0] = this->matrixTransform*Vector(center.x+r, center.y+r, center.z+r);
            ps[1] = this->matrixTransform*Vector(center.x+r, center.y+r, center.z-r);
            ps[2] = this->matrixTransform*Vector(center.x+r, center.y-r, center.z+r);
            ps[3] = this->matrixTransform*Vector(center.x+r, center.y-r, center.z-r);
            ps[4] = this->matrixTransform*Vector(center.x-r, center.y+r, center.z+r);
            ps[5] = this->matrixTransform*Vector(center.x-r, center.y+r, center.z-r);
            ps[6] = this->matrixTransform*Vector(center.x-r, center.y-r, center.z+r);
            ps[7] = this->matrixTransform*Vector(center.x-r, center.y-r, center.z-r);
            this->UR = Vector(INT_MIN,INT_MIN,INT_MIN);
            this->LL = Vector(INT_MAX,INT_MAX,INT_MAX);
            for (int i = 0; i < 8; i++) {
                Vector aVec = Vector(center.x+r, center.y+r, center.z+r);
                if (ps[i].x < LL.x) {
                    this->LL.x = ps[i].x;
                }
                if (ps[i].y < this->LL.y) {
                    this->LL.y = ps[i].y;
                }
                if (ps[i].z < this->LL.z) {
                    this->LL.z = ps[i].z;
                }
                if (ps[i].x > this->UR.x) {
                    this->UR.x = ps[i].x;
                }
                if (ps[i].y > this->UR.y) {
                    this->UR.y = ps[i].y;
                }
                if (ps[i].z > this->UR.z) {
                    this->UR.z = ps[i].z;
                }
            }
            mtTransposed = this->matrixTransform.transpose();
        }
    Sphere(Coord center, float r) :
        center(center),
        r(r)
        { }
    Vector LL;
    Vector UR;
    Matrix preTransform;
    Matrix notInvertedTransform;
    Matrix matrixTransform;
    Matrix mtTransposed;
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
