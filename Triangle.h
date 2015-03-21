#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Coord.h"
#include "Shape.h"
#include "Transform.h"

class Triangle: public Shape {
  public:
    Matrix matrixTransform;
    Matrix preTransform;
    Matrix mtTransposed;
    Triangle () {}
    Triangle(Coord point1, Coord point2, Coord point3, Material material, Matrix transMatrix2) :
        point1(point1),
        point2(point2),
        point3(point3), 
        hasNormal(0)                               
        {
            this->setMaterial(material);
            this->preTransform = Matrix(transMatrix2);
            this->notInvertedTransform = preTransform.copy();
            this->matrixTransform = Matrix();
            MatrixInversion(this->preTransform.matrix, 4, this->matrixTransform.matrix);
            Vector p1;
            Vector p2;
            Vector p3;
            Vector ps[3] = {};
            Vector vec1 = Vector(point1.x, point1.y, point1.z);
            Vector vec2 = Vector(point2.x, point2.y, point2.z);
            Vector vec3 = Vector(point3.x, point3.y, point3.z);
            ps[0] = this->matrixTransform*vec1;
            ps[1] = this->matrixTransform*vec2;
            ps[2] = this->matrixTransform*vec3;
            this->UR = Vector(INT_MIN,INT_MIN,INT_MIN);
            this->LL = Vector(INT_MAX,INT_MAX,INT_MAX);
            for (int i = 0; i < 8; i++) {
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
    Triangle(Coord point1, Coord point2, Coord point3, Matrix transMatrix2) :
        point1(point1),
        point2(point2),
        point3(point3),
        hasNormal(0)                
        {
            this->preTransform = Matrix(transMatrix2);
            this->notInvertedTransform = preTransform.copy();
            this->matrixTransform = Matrix();
            MatrixInversion(this->preTransform.matrix, 4, this->matrixTransform.matrix);
            Vector p1;
            Vector p2;
            Vector p3;
            Vector ps[3] = {};
            Vector vec1 = Vector(point1.x, point1.y, point1.z);
            Vector vec2 = Vector(point2.x, point2.y, point2.z);
            Vector vec3 = Vector(point3.x, point3.y, point3.z);
            ps[0] = this->matrixTransform*vec1;
            ps[1] = this->matrixTransform*vec2;
            ps[2] = this->matrixTransform*vec3;
            this->UR = Vector(INT_MIN,INT_MIN,INT_MIN);
            this->LL = Vector(INT_MAX,INT_MAX,INT_MAX);
            for (int i = 0; i < 8; i++) {
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
    Triangle(Coord point1, Coord point2, Coord point3, Vector vn1, Vector vn2, Vector vn3, Matrix transMatrix2) :
        point1(point1),
        point2(point2),
        point3(point3),
        vn1(vn1),
        vn2(vn2),
        vn3(vn3),
        hasNormal(1)                
        {
            this->preTransform = Matrix(transMatrix2);
            this->notInvertedTransform = preTransform.copy();
            this->matrixTransform = Matrix();
            MatrixInversion(this->preTransform.matrix, 4, this->matrixTransform.matrix);
            Vector p1;
            Vector p2;
            Vector p3;
            Vector ps[3] = {};
            Vector vec1 = Vector(point1.x, point1.y, point1.z);
            Vector vec2 = Vector(point2.x, point2.y, point2.z);
            Vector vec3 = Vector(point3.x, point3.y, point3.z);
            ps[0] = this->matrixTransform*vec1;
            ps[1] = this->matrixTransform*vec2;
            ps[2] = this->matrixTransform*vec3;
            this->UR = Vector(INT_MIN,INT_MIN,INT_MIN);
            this->LL = Vector(INT_MAX,INT_MAX,INT_MAX);
            for (int i = 0; i < 8; i++) {
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
    Triangle(Coord point1, Coord point2, Coord point3, Vector vn1, Vector vn2, Vector vn3, Material material, Matrix transMatrix2) :
        point1(point1),
        point2(point2),
        point3(point3),
        vn1(vn1),
        vn2(vn2),
        vn3(vn3),
        hasNormal(1)                
        {
            this->setMaterial(material);
            this->preTransform = Matrix(transMatrix2);
            this->notInvertedTransform = preTransform.copy();
            this->matrixTransform = Matrix();
            MatrixInversion(this->preTransform.matrix, 4, this->matrixTransform.matrix);
            Vector p1;
            Vector p2;
            Vector p3;
            Vector ps[3] = {};
            Vector vec1 = Vector(point1.x, point1.y, point1.z);
            Vector vec2 = Vector(point2.x, point2.y, point2.z);
            Vector vec3 = Vector(point3.x, point3.y, point3.z);
            ps[0] = this->matrixTransform*vec1;
            ps[1] = this->matrixTransform*vec2;
            ps[2] = this->matrixTransform*vec3;
            this->UR = Vector(INT_MIN,INT_MIN,INT_MIN);
            this->LL = Vector(INT_MAX,INT_MAX,INT_MAX);
            for (int i = 0; i < 8; i++) {
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
    Vector LL;
    Vector UR;       
    Coord point1;
    Coord point2;
    Coord point3;
    Matrix notInvertedTransform;
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
