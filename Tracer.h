#ifndef TRACER_H
#define TRACER_H

#include "Ray.h"
#include "Color.h"
#include "Triangle.h"
#include "Sphere.h"
#include "Shape.h"
#include "HitRecord.h"
#include "Shader.cpp"
using namespace std;

//Ray.start <- coord, Ray.direction <-vec

class Tracer {
 public:
   vector<Shape*> all_shapes;
   Tracer(vector<Shape*> all_shapes) : all_shapes(all_shapes){}
   Color trace(HitRecord hitRecord, vector<Light> lights, Vector rayDirection);
   HitRecord hit(Ray ray);
   HitRecord raySphere(Ray r, Sphere* s, float tMin, float tMax);
   HitRecord rayTri(Ray r, Triangle* tri, float tMin, float tMax);
};
//Tmin, max = 1, 100 arbitrarily

HitRecord Tracer::hit(Ray ray) {
  HitRecord hitRecord = HitRecord(false);
	float t_min = ray.tMin;
	float t_max = ray.tMax;
	HitRecord temp = HitRecord(false);
	for (int i = 0; i < all_shapes.size(); i++) {
		Triangle* triangle = dynamic_cast<Triangle*>(all_shapes[i]);
		Sphere* sphere = dynamic_cast<Sphere*>(all_shapes[i]);
 		if (triangle != 0) { //if it's a triangle?
			//cout << "HI IM TRIANGLE! " << endl;
      temp = rayTri(ray, triangle, t_min, t_max);
			if (temp.isHit) {
				hitRecord = temp;
				t_max = temp.t;
				//hitobject = all_shapes[i].shape
				//t_max = //t that was hit
			}
 		}
 		if (sphere != 0) {
 			//cout << "YO IM SPHERE! " << endl;
      temp = raySphere(ray, sphere, t_min, t_max);
			if (temp.isHit) {
				hitRecord = temp;
				t_max = temp.t;
				//hitobject = all_shapes[i].shape
				//t_max = //t that was hit
			}
 		}
	}
	return hitRecord;
}

Color Tracer::trace(HitRecord hitRecord, vector<Light> lights, Vector rayDirection) {

 //TO DO: IMPLEMENT SHADER HERE. currently just sets color to red if shape is there
 //luckily material properties are stored in all_shapes

  float epsilon = .01;
  Color total = Color(0,0,0);
  for(std::vector<Light *>::iterator itor=(Light::lights).begin(); itor!=Light::lights.end(); ++itor) {
    
    Vector lightLocationVec = Vector((*itor)->location.x,(*itor)->location.y,(*itor)->location.z);
    Vector intersectionVec = Vector(hitRecord.intersection.x,hitRecord.intersection.y,hitRecord.intersection.z);
    Vector lightDirectionVec;
    Color lightColor = (*itor)->color;

    if ((*itor)->type == DIRECTIONAL) {
      lightDirectionVec = lightLocationVec*(-1);
    } else if ((*itor)->type == POINT) {
      lightDirectionVec = lightLocationVec-intersectionVec;
    }
    lightDirectionVec = lightDirectionVec.normalize();


	  Ray shadow = Ray(hitRecord.intersection, lightDirectionVec, 5, epsilon, INFINITY);
	  HitRecord shadowHR = this->hit(shadow);
    if (shadowHR.isHit) {
    	if (shadowHR.isSphere) { //TODO: shadowHR or hitRecord?
    		total = shadowHR.sphere.material.ambient*lightColor;
    	}
    	else {
    		total = shadowHR.triangle.material.ambient*lightColor;
    	}
      return total;
    }
    else {
			 total = shadeCircle(hitRecord, lightDirectionVec, rayDirection, lightColor);
    }

  }

 // cout << "FINAL COLOR";
 // cout << color;
 return total;
 // return Color(1, 0, 1);
}

HitRecord Tracer::raySphere(Ray r, Sphere* s, float tMin, float tMax) {
//sph coord center float r
//ray coord start v direction
	float t = -INFINITY;
	float t2 = -INFINITY;
	Vector d = r.direction;
	Vector c = Vector((s->center).x, (s->center).y, (s->center).z);
	Vector e = Vector(r.start.x, r.start.y, r.start.z);
	Vector e_minus_c = e - c;
	float d_dot = d.dot(d);
	float discrimnant = sqrt(pow((d.dot(e_minus_c)),2) - d_dot * (e_minus_c.dot(e_minus_c) - (s->r * s->r)));
	if (discrimnant < 0)
		return HitRecord(false);
	if (discrimnant == 0)
		t = -(d.dot(e_minus_c) / d_dot);
	if (discrimnant > 0) {
		t = -((d.dot(e_minus_c) + discrimnant) / d_dot);
		t2 = -((d.dot(e_minus_c) - discrimnant) / d_dot);
	}
	if (t < tMin && t2 < tMin) { //equiv to t1, t2 < 0
		return HitRecord(false);
	}
	if (t > tMax && t2 > tMax) {
		return HitRecord(false);
	}
	else {
		if (t > tMin && t < tMax) {
			//return obj with t1
			Vector p = r.eval(t);
      Coord intersection = Coord(p.x, p.y, p.z);
			Vector normal = (p - c)/s->r;
      Sphere sphere = *s;
			return HitRecord(t, intersection, normal, sphere);
		}
		else if (t2 > tMin && t2 < tMax) {
			//return obj with t2
			Vector p = r.eval(t2);
      Coord intersection = Coord(p.x, p.y, p.z);
			Vector normal = (p - c)/s->r;
      Sphere sphere = *s;
			return HitRecord(t2, intersection, normal, sphere);
		}
	}
	return HitRecord(false);
}

HitRecord Tracer::rayTri(Ray r, Triangle* tri, float tMin, float tMax) {
//CALCULATIONS AS PER PG 79 OF TEXTBOOK
  Vector x = Vector(tri->point1.x, tri->point2.x, tri->point3.x);
  // x = (xa, xb, xc) of triangles
  Vector y = Vector(tri->point1.y, tri->point2.y, tri->point3.y);
  Vector z = Vector(tri->point1.z, tri->point2.z, tri->point3.z);
  Vector d = r.direction;
  Vector e = Vector(r.start.x, r.start.y, r.start.z);

  //cout << "X, Y, Z " << x << y << z <<endl;
  //cout<< "D and E" << d << e << endl;

  float ei_m_hf = (y.x - y.z)*(d.z) - (d.y)*(z.x - z.z);
  float gf_m_di = (d.x)*(z.x - z.z) - (x.x - x.z)*(d.z);
  float dh_m_eg = (x.x - x.z)*d.y - (y.y - y.z)*d.x;
  float ak_m_jb = (x.x - x.y)*(y.x - e.y) - (x.x - e.x)*(y.x - y.y);
  float jc_m_al = (x.x - e.x)*(z.x - z.y) - (x.x - x.y)*(z.x - e.z);
  float bl_m_kc = (y.x - y.y)*(z.x - e.z) - (y.x - e.y)*(z.x - z.y);

  float m = (x.x - x.y)*ei_m_hf + (y.x - y.y)*gf_m_di + (z.x - z.y)*dh_m_eg;
  float t = -((z.x - z.z)*ak_m_jb + (y.x - y.z)*jc_m_al + (x.x - x.z)*bl_m_kc)/m;

  if ((t < tMin) || (t > tMax)) {
  	//cout << "this happened 1 " << endl;
  	return HitRecord(false);

  }
  float gamma = (d.z*ak_m_jb + d.y*jc_m_al + d.x*bl_m_kc)/m;
  if (gamma < 0 || gamma > 1) {
  	//cout << "this happened 2 " << endl;

  	return HitRecord(false);

  }
  float beta = ((x.x - e.x)*ei_m_hf + (y.x - e.y)*gf_m_di + (z.x - e.z)*dh_m_eg) / m;
	if (beta < 0 || beta > 1 - gamma) {
  	//cout << "this happened 3 " << endl;

		return HitRecord(false);

	}
	Vector p1 = Vector(tri->point1.x, tri->point1.y, tri->point1.z);
	Vector p2 = Vector(tri->point2.x, tri->point2.y, tri->point2.z);
	Vector p3 = Vector(tri->point3.x, tri->point3.y, tri->point3.z);
  Vector p = r.eval(t);
  Coord intersection = Coord(p.x, p.y, p.z);
	Vector normal = (p2 - p1).cross(p3 - p1);
  Triangle triangle = *tri;
    	//cout << "the end good job " << endl;

  return HitRecord(t, intersection, normal, triangle);
}

#endif
