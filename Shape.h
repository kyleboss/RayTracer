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
};
#endif
