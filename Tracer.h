#ifndef TRACER_H
#define TRACER_H

#include "Ray.h"
#include "Color.h"
#include "Triangle.h"

using namespace std;

//Ray.start <- coord, Ray.direction <-vec

class Tracer {
  public:
    vector<Shape> all_shapes;
    Tracer(vector<Shape> all_shapes) : all_shapes(all_shapes){}
    Color trace(Ray ray);
    bool hit(Ray ray);
    bool raySphere(Ray r, Sphere s, float tMin, float tMax);
    bool rayTri(Ray r, Triangle t, float tMin, float tMax);
};
//Tmin, max = 1, 100 arbitrarily 

bool Tracer::hit(Ray ray) {
	bool hit = false;
	float t_min = 0;
	float t_max = 100;
	for (int i = 0; i < all_shapes.size(); i++) {
  		if (typeof(all_shapes[i].shape) == Triangle) {
			if (rayTri(ray, all_shapes[i].shape, t_min, t_max) {
				hit = true;
				//hitobject = all_shapes[i].shape
				t_max = //t that was hit
			}  			
  		}
  		if (typeof(all_shapes[i].shape) == Sphere) {
			if (raySphere(ray, all_shapes[i].shape, t_min, t_max) {
				hit = true;
				//hitobject = all_shapes[i].shape
				t_max = //t that was hit
			}
  		}
	}
	return hit;
}

Color Tracer::trace(Ray ray) {

  //TO DO: IMPLEMENT SHADER HERE. currently just sets color to red if shape is there
  //luckily material properties are stored in all_shapes
  Color color = Color(1, 0, 0);
  return color;
};

bool Tracer::raySphere(Ray r, Sphere s, float tMin, float tMax) {
	//sph coord center float r
	//ray coord start v direction
	Vector d = r.direction;
	Vector c(s.center.x, s.center.y, c.center.z);
	Vector e(r.start.x, r.start.y, r.start.z);
	Vector e_minus_c = e - c;
	float d_dot = d.dot(d);
	float discrimnant = sqrt(pow((d.dot(e_minus_c)),2) - d_dot * (e_minus_c.dot(e_minus_c) - (s.r * s.r)));
	if (discrimnant < 0)
		return false
	if (discrimnant == 0)

	return false
}

bool Tracer::rayTri(Ray r, Triangle t, float tMin, float tMax) {
   Vector a(Triangle.point1.x, Triangle.point1.y, Triangle.point1.z); 
   Vector b(Triangle.point2.x, Triangle.point2.y, Triangle.point2.z);
   Vector c(Triangle.point3.x, Triangle.point3.y, Triangle.point3.z);
   return false
}

#endif