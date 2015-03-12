#ifndef SHAPE_H
#define SHAPE_H
#include "Material.h"
class Shape {
  public:
    Shape() { }
    Material material;
    void setMaterial (Material material) {
      this->material = material;
    }
    virtual std::basic_ostream<char, std::__1::char_traits<char> > print() {};
};

std::ostream& operator<< (std::ostream &out, Shape &shape)
{
    out << "Shape: " << shape.print() <<
        "Material: " << shape.material << "\n";
    return out;
}
#endif