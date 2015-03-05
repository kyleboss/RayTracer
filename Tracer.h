#include <vector>
#include "Triangle.h"
#include "Color.h"
#include "Ray.h"

class Tracer {
  public:
    vector<Triangle> objects;
    Tracer(vector<Triangle> objects) : objects(objects) {}
    Color trace(Ray ray);
};
