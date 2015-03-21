#ifndef COORD_H
#define COORD_H

// #include "Vector.h"

class Coord {
  public:
    Coord (float x, float y, float z) :
    x(x),
    y(y),
    z(z)
    {}
    Coord () { }
    static Coord midPoint(Coord c1, Coord c2);
    float x;
    float y;
    float z;
    Coord operator * (Coord c);
    Coord operator * (float s);
    Coord operator + (Coord c);
    Coord operator - (Coord c);
    Coord operator - (float f);
    Coord operator + (float f);
};

Coord Coord::midPoint(Coord c1, Coord c2) {
    return Coord ((c1.x+c2.x)/2, (c1.y+c2.y)/2, (c1.z+c2.z)/2);
}

std::ostream& operator<< (std::ostream &out, Coord &coord)
{
    out << "(" << coord.x << ", " <<
        coord.y << ", " <<
        coord.z << ")";
    return out;
}

Coord Coord::operator * (Coord c) {
  return Coord(x * c.x, y * c.y, z * c.z);
};

Coord Coord::operator * (float s) {
  return Coord(x * s, y * s, z * s);
};

Coord Coord::operator + (Coord c) {
  return Coord(x + c.x, y + c.y, z + c.z);
};

Coord Coord::operator - (Coord c) {
  return Coord(x - c.x, y - c.y, z - c.z);
};

Coord Coord::operator - (float f) {
  return Coord(x - f, y - f, z - f);
};

Coord Coord::operator + (float f) {
  return Coord(x + f, y + f, z + f);
};

#endif
