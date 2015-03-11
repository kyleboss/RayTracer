#ifndef TRACER_H
#define TRACER_H

#include "Ray.h"
#include "Color.h"
#include "Triangle.h"
#include "Sphere.h"
#include "Shape.h"

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
/*float t_min = 0;
float t_max = 100;
for (int i = 0; i < all_shapes.size(); i++) {
 		if (typeof(all_shapes[i].shape) == Triangle) {
		if (rayTri(ray, all_shapes[i], t_min, t_max) {
			hit = true;
			//hitobject = all_shapes[i].shape
			t_max = //t that was hit
		}  			
 		}
 		if (typeof(all_shapes[i].shape) == Sphere) {
		if (raySphere(ray, all_shapes[i], t_min, t_max) {
			hit = true;
			//hitobject = all_shapes[i].shape
			t_max = //t that was hit
		}
 		}
}*/
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
	float t = -INFINITY;
	Vector d = r.direction;
	Vector c = Vector((s.center).x, (s.center).y, (s.center).z);
	Vector e = Vector(r.start.x, r.start.y, r.start.z);
	Vector e_minus_c = e - c;
	float d_dot = d.dot(d);
	float discrimnant = sqrt(pow((d.dot(e_minus_c)),2) - d_dot * (e_minus_c.dot(e_minus_c) - (s.r * s.r)));
	if (discrimnant < 0)
		return false;
	if (discrimnant == 0)
		t = -(d.dot(e_minus_c) / d_dot);
	else {
		t = -((d.dot(e_minus_c) + discrimnant) / d_dot);
		float t2 = -((d.dot(e_minus_c) - discrimnant) / d_dot); 
	}
	return true;
	//remember to set normal
}

bool Tracer::rayTri(Ray r, Triangle tri, float tMin, float tMax) {
//CALCULATIONS AS PER PG 79 OF TEXTBOOK
  Vector x = Vector(tri.point1.x, tri.point2.x, tri.point3.x); 
  // x = (xa, xb, xc) of triangles
  Vector y = Vector(tri.point1.y, tri.point2.y, tri.point3.y);
  Vector z = Vector(tri.point1.z, tri.point2.z, tri.point3.z);
  Vector d = r.direction;
  Vector e = Vector(r.start.x, r.start.y, r.start.z);

  float ei_m_hf = (y.y - y.z)*(d.z) - (d.y)*(z.x - z.z);
  float gf_m_di = (d.x)*(z.x - z.z) - (x.x - x.z)*(d.z);
  float dh_m_eg = (x.x - x.z)*(z.x - z.z) - (y.y - y.z)*(z.z - z.y);
  float ak_m_jb = (x.x - x.y)*(y.y - e.y) - (x.x - e.x)*(y.y - y.y);
  float jc_m_al = (x.x - e.x)*(z.x - z.y) - (x.x - x.y)*(z.x - e.z);
  float bl_m_kc = (y.y - y.y)*(z.x - e.z) - (y.y - e.y)*(z.x - z.y);

  float m = (x.x - x.y)*ei_m_hf + (y.y - y.y)*gf_m_di + (z.x - z.y)*dh_m_eg;
  float t = -((z.x - z.z)*ak_m_jb + (y.y - y.z)*jc_m_al + (x.x - x.z)*bl_m_kc)/m;

  if ((t < tMin) || (t > tMax))
  	return false;
  float gamma = (d.z*ak_m_jb + d.y*jc_m_al + d.x*bl_m_kc)/m;
  if (gamma < 0 || gamma > 1)
  	return false;
  float beta = ((x.x - e.x)*ei_m_hf + (y.y - e.y)*gf_m_di + (z.x - e.z)*dh_m_eg) / m;
	if (beta < 0 || beta > 1)
		return false;  
  return true;
  //remember to set normal
}

#endif