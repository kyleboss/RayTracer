#include <math.h>
#include <iostream>
#include "Vector.h"

double Vector::magnitude() {
  return sqrtf(x*x + y*y + z*z);
};

Vector Vector::normalize() {
  return *this = *this / this->magnitude();
};

Vector Vector::cross(Vector v) {
  return Vector(y*v.z - v.y*z, v.x*z - x*v.z, x*v.y - v.x*y);
};

double Vector::dot(Vector v) {
  return x*v.x + y*v.y + z*v.z;
};

Vector Vector::operator + (Vector v) {
  return Vector(x + v.x, y + v.y, z + v.z);
};

Vector Vector::operator - (Vector v) {
  return Vector(x - v.x, y - v.y, z - v.z);
};

Vector Vector::operator * (Vector v) {
  return Vector(x * v.x, y * v.y, z * v.z);
};


Vector Vector::operator / (Vector v) {
  return Vector(x / v.x, y / v.y, z / v.z);
};


Vector Vector::operator * (double c) {
  return Vector(c*x, c*y, c*z);
};

Vector Vector::operator / (double c) {
  return Vector(x/c, y/c, z/c);
};

int main(int argc, char* argv[]) {
  return 0;
};
