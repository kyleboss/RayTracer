#ifndef VECTOR_H
#define VECTOR_H

class Vector {
  public:
    float x, y, z;
    Vector(float x, float y, float z) : x(x), y(y), z(z) {}
    Vector normalize();
    Vector cross(Vector v);
    float dot(Vector v);
    float magnitude();
    Vector operator + (Vector v);
    Vector operator - (Vector v);
    Vector operator * (Vector v);
    Vector operator / (Vector v);
    Vector operator * (float c);
    Vector operator / (float c);
};

#endif
