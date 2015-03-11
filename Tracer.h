#ifndef TRACER_H
#define TRACER_H

#include "Ray.h"
#include "Color.h"
#include "Triangle.h"

using namespace std;

//Ray.start, Ray.direction

class Tracer {
  public:
    vector<Triangle> objects;
    vector<Sphere> spheres;
    Tracer(vector<Triangle> objects, vector<Sphere> spheres) : objects(objects) spheres(spheres){}
    Color trace(Ray ray);
    bool raySphere(Ray r, Sphere s, float tMin, float tMax);
    bool rayTri(Ray r, Triangle t, float tMin, float tMax);
};

Color Tracer::trace(Ray ray) {
  
  Color color = Color(1, 1, 1);
  return color;
};

bool Tracer::raySphere(Ray r, Sphere s, float tMin, float tMax) {
	return false
    }

bool Tracer::rayTri(Ray r, Triangle t, float tMin, float tMax) {
   Vector a(Triangle.point1.x, Triangle.point1.y, Triangle.point1.z); 
   Vector b(Triangle.point2.x, Triangle.point2.y, Triangle.point2.z);
   Vector c(Triangle.point3.x, Triangle.point3.y, Triangle.point3.z);
   return false
}

#endif