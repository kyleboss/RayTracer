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
    virtual void print(std::ostream &out) =0;
};

std::ostream& operator<< (std::ostream &out, Shape &shape)
{
    out << typeid(shape).name();
    shape.print(out);
    return out;
}
#endif