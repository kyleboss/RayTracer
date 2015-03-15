
#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>
#include <time.h>
#include <math.h>


#include "Light.h"

const int AMBIENT = 0;
const int DIRECTIONAL = 1;
const int POINT = 2;
using namespace std;


Color shadeCircle(HitRecord hitRecord, Vector lightDirectionVec, Vector rayDirection, Color lightColor) {
  Sphere sphere = hitRecord.sphere;
  Triangle triangle = hitRecord.triangle;
  float x = hitRecord.intersection.x;
  float y = hitRecord.intersection.y;

      Color total = Color(0,0,0);
       float ln = lightDirectionVec.dot(hitRecord.normal);
      float diffPos = max(0.0f, ln); //max(l.n, 0)
      Vector r = hitRecord.normal;
      r=r*(2*ln);
      r=r-lightDirectionVec;
      r=r.normalize();
      Color ambient, diffuse, specular;
      float specPos;
      Vector w = rayDirection*(-1);
      w = w.normalize();
      if (hitRecord.isSphere) {
        specPos = pow(max(0.0f, r.dot(w)), sphere.material.exp); // CHECK v
        ambient = sphere.material.ambient*lightColor;
        diffuse = sphere.material.diffuse*lightColor;
        specular = sphere.material.specular*lightColor;
      } else {
        specPos = pow(max(0.0f, r.dot(w)), triangle.material.exp); // CHECK v
        ambient = triangle.material.ambient*lightColor;
        diffuse = triangle.material.diffuse*lightColor;
        specular = triangle.material.specular*lightColor;              
      }
      diffuse = diffuse.scale(diffPos);
      diffuse.scale(diffPos);
      specular.scale(specPos);
      total = total + ambient + diffuse + specular; 
      // cout << "exp" << shape.material.exp;
      cout << "specPos" << specPos;
      cout << "specular" << specular;
      return total;

}
