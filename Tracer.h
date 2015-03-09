#ifndef TRACER_H
#define TRACER_H

#include "Ray.h"
#include "Color.h"
#include "Triangle.h"

using namespace std;

class Tracer {
  public:
    vector<Triangle> objects;
    Tracer(vector<Triangle> objects) : objects(objects) {}
    Color trace(Ray ray);
};

Color Tracer::trace(Ray ray) {
  Color color = Color(1, 1, 1);
  return color;
};

#endif