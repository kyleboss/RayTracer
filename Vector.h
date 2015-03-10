#ifndef VECTOR_H
#define VECTOR_H

class Vector {
  public:
    float x, y, z;
    Vector(float x, float y, float z) : x(x), y(y), z(z) {}
    Vector() : x(0), y(0), z(0) {}
    Vector normalize();
    Vector cross(Vector v);
    float dot(Vector v);
    float magnitude();
    Vector operator + (Vector v);
    Vector operator - (Vector v);
    Vector operator - (Coord v);
    Vector operator * (Vector v);
    Vector operator / (Vector v);
    Vector operator * (float c);
    Vector operator / (float c);
};

float Vector::magnitude() {
  return sqrtf(x*x + y*y + z*z);
};

Vector Vector::normalize() {
  return *this / this->magnitude();
};

Vector Vector::cross(Vector v) {
  return Vector(y*v.z - v.y*z, v.x*z - x*v.z, x*v.y - v.x*y);
};

float Vector::dot(Vector v) {
  return x*v.x + y*v.y + z*v.z;
};

Vector Vector::operator + (Vector v) {
  return Vector(x + v.x, y + v.y, z + v.z);
};

Vector Vector::operator - (Vector v) {
  return Vector(x - v.x, y - v.y, z - v.z);
};

Vector Vector::operator - (Coord c) {
  return Vector(x - c.x, y - c.y, z - c.z);
};

Vector Vector::operator * (Vector v) {
  return Vector(x * v.x, y * v.y, z * v.z);
};


Vector Vector::operator / (Vector v) {
  return Vector(x / v.x, y / v.y, z / v.z);
};


Vector Vector::operator * (float c) {
  return Vector(c*x, c*y, c*z);
};

Vector Vector::operator / (float c) {
  return Vector(x/c, y/c, z/c);
};

std::ostream& operator<< (std::ostream &out, Vector &vector)
{
    out << "(" << vector.x << ", " <<
        vector.y << ", " <<
        vector.z << ")\n";
    return out;
}

#endif
