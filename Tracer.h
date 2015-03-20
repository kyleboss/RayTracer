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
   HitRecord raySphere(Ray r, Sphere* s, float tMin, float tMax, int bounces);
   HitRecord rayTri(Ray r, Triangle* tri, float tMin, float tMax, int bounces);
};

HitRecord Tracer::hit(Ray ray) {
  HitRecord hitRecord = HitRecord(false);
  float t_min = ray.tMin;
  float t_max = ray.tMax;
  HitRecord temp = HitRecord(false);
  for (int i = 0; i < all_shapes.size(); i++) {
    Triangle* triangle = dynamic_cast<Triangle*>(all_shapes[i]);
    Sphere* sphere = dynamic_cast<Sphere*>(all_shapes[i]);
    Ray newRay;
    if (triangle != 0) { //if it's a triangle?
          Coord rayStartCoord = ray.start;
          Vector rayStartVec = Vector(rayStartCoord.x, rayStartCoord.y, rayStartCoord.z);
          rayStartVec = triangle->matrixTransform*rayStartVec;
          rayStartCoord = Coord(rayStartVec.x, rayStartVec.y, rayStartVec.z);
          Vector rayDir = ray.direction;
          rayDir = triangle->matrixTransform.multiplyDir(rayDir);
          rayDir = rayDir.normalize();
          newRay = Ray(rayStartCoord, rayDir, ray.bouncesLeft, ray.tMin, ray.tMax);
          temp = rayTri(newRay, triangle, t_min, t_max, ray.bouncesLeft);
      if (temp.isHit) {
        hitRecord = temp;
        t_max = temp.t;
        //hitobject = all_shapes[i].shape
        //t_max = //t that was hit
      }
    }
    if (sphere != 0) {
      //cout << "YO IM SPHERE! " << endl;
         //temp = raySphere(ray, sphere, t_min, t_max);
          Coord rayStartCoord = ray.start;
          Vector rayStartVec = Vector(rayStartCoord.x, rayStartCoord.y, rayStartCoord.z);
          rayStartVec = sphere->matrixTransform*rayStartVec;
          rayStartCoord = Coord(rayStartVec.x, rayStartVec.y, rayStartVec.z);
          Vector rayDir = ray.direction;
          //rayDir = sphere->matrixTransform * rayDir;
  
          rayDir = sphere->matrixTransform.multiplyDir(rayDir);
          rayDir = rayDir.normalize();
          newRay = Ray(rayStartCoord, rayDir, ray.bouncesLeft, ray.tMin, ray.tMax);          
          temp = raySphere(newRay, sphere, t_min, t_max, ray.bouncesLeft);
      if (temp.isHit) {
      	//cout << "HIT!" << endl;
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
  float epsilon = .25;
  Color total = Color(0,0,0);

  for(int i = 0; i < lights.size(); i++) {
    Vector lightLocationVec = Vector(lights[i].location.x,lights[i].location.y,lights[i].location.z);
    Vector intersectionVec = Vector(hitRecord.intersection.x, hitRecord.intersection.y, hitRecord.intersection.z);

    Vector lightDirectionVec;
    Color lightColor = lights[i].color;
    int lightType = lights[i].type;

    if (lightType == DIRECTIONAL) {
      lightDirectionVec = lightLocationVec*(-1);
    } else if (lightType == POINT) {
    	    cout << "INTER! " << intersectionVec << endl;

      lightDirectionVec = lightLocationVec - intersectionVec;
          cout << "LDV!1 " << lightDirectionVec << endl;

    }
    float r = lightDirectionVec.magnitude();
              cout << "LDV!Before " << lightDirectionVec << endl;

    lightDirectionVec = lightDirectionVec.normalize();
          cout << "LDV!After " << lightDirectionVec << endl;
    Ray shadow = Ray(hitRecord.intersection, lightDirectionVec, 5, epsilon, INFINITY);
    HitRecord shadowHR = this->hit(shadow);

    if (shadowHR.isHit) {
      if (lightType == AMBIENT) {
        if (hitRecord.isSphere) {
          total = total + hitRecord.sphere.material.ambient*lightColor;
        }
        else {
          total = total + hitRecord.triangle.material.ambient*lightColor;
        }
      }
    }
    else {
       total = total + shadeCircle(hitRecord, lightDirectionVec, rayDirection, lightColor, lightType);
    }
    //attenuation!
    if (lightType == POINT) {
      int falloff = lights[i].falloff;
      if (falloff != 0) {
        if (falloff == 1) {
          total = total.scale(1/r);
        }
        else if (falloff == 2) {
          total = total.scale(1/(r*r));
        }
      }
    }
  }
  //reflection
  //check if necessary
  bool isreflective;
  Color reflectance;
  if (hitRecord.isSphere) {
    reflectance = hitRecord.sphere.material.reflective;
  } else {
    reflectance = hitRecord.triangle.material.reflective;
  }

  if (!(reflectance.r == 0 & reflectance.g == 0 & reflectance.b == 0)) {
    isreflective = true;    
  }
  if(hitRecord.bounces > 0 && isreflective == true) {
  	Vector l = (rayDirection * -1).normalize();
  	Vector n = hitRecord.normal.normalize();
    Vector r = (l * -1) + n * 2 * (l).dot(n);
    r = r.normalize();
    Ray reflect = Ray(hitRecord.intersection, r, hitRecord.bounces - 1, epsilon, INFINITY);
    HitRecord rHit = hit(reflect);
    if(rHit.isHit) {
        total = total + reflectance * trace(rHit, lights, reflect.direction);
      }
    }
 return total;
}

HitRecord Tracer::raySphere(Ray r, Sphere* s, float tMin, float tMax, int bounces) {
//sph coord center float r
//ray coord start v direction
  float t = -INFINITY;
  float t2 = -INFINITY;
  Vector d = r.direction;
  Vector c = Vector((s->center).x, (s->center).y, (s->center).z);
  Vector e = Vector(r.start.x, r.start.y, r.start.z);
  Vector e_minus_c = e - c;
  // cout << "MatrixTransform\n" << s->matrixTransform;
  // e_minus_c = (s->matrixTransform)*e_minus_c;
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
  	//cout << "T is " << t << " T2 is " << t2 << endl;
  	  //	cout << "Tmin is " << tMin << " Tmax is " << tMax << endl;
    if (t > tMin && t < tMax) {
      //return obj with t1
      Vector p = r.eval(t);
      Vector intersectionVec = Vector(p.x, p.y, p.z);
      intersectionVec = s->notInvertedTransform*intersectionVec;
      Coord intersection = Coord(intersectionVec.x, intersectionVec.y, intersectionVec.z);
      Vector normal = (p - c) * 2;
      //cout << "OLD NORM " << normal << endl;
      normal = s->mtTransposed.multiplyDir(normal);

      Sphere sphere = *s;
      // cout << sphere.matrixTransform;
      // Matrix invertedMatrix = Matrix::invert(sphere.matrixTransform);
      return HitRecord(t, intersection, normal, sphere, bounces, r);
    }
    else if (t2 > tMin && t2 < tMax) {
    	//cout << "inside if2 " << endl;
      //return obj with t2
      Vector p = r.eval(t2);
      Vector intersectionVec = Vector(p.x, p.y, p.z);
      intersectionVec = s->notInvertedTransform*intersectionVec;
      Coord intersection = Coord(intersectionVec.x, intersectionVec.y, intersectionVec.z);
      Vector normal = (p - c) * 2;
         //   cout << "OLD NORM " << normal << endl;
            normal = s->mtTransposed.multiplyDir(normal);

      Sphere sphere = *s;
    return HitRecord(t2, intersection, normal, sphere, bounces, r);
    }
  }
  return HitRecord(false);
}

HitRecord Tracer::rayTri(Ray r, Triangle* tri, float tMin, float tMax, int bounces) {
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
  float dh_m_eg = (x.x - x.z)*d.y - (y.x - y.z)*d.x;
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
  Vector intersectionVec = Vector(p.x, p.y, p.z);
  intersectionVec = tri->notInvertedTransform*intersectionVec;
  Coord intersection = Coord(intersectionVec.x, intersectionVec.y, intersectionVec.z);
	Vector normal = (p2 - p1).cross(p3 - p1).normalize();
  normal = tri->mtTransposed.multiplyDir(normal);
	if (tri->hasNormal) { //for obj parsing
		Vector na = tri->vn1;
		Vector nb = tri->vn2;
		Vector nc = tri->vn3;
		normal = (na + (nb - na)*beta + (nc - na)*gamma).normalize();
	}
	Triangle triangle = *tri;
  return HitRecord(t, intersection, normal, triangle, bounces, r);
}

#endif
