
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


Color shadeCircle(HitRecord hitRecord, Vector lightDirectionVec, Vector rayDirection, Color lightColor, int lightType) {
  
  Sphere sphere = hitRecord.sphere;
  Triangle triangle = hitRecord.triangle;

  Vector n = hitRecord.normal.normalize();
  Color total = Color(0,0,0);
  Color ambient, diffuse, specular;

  if (lightType == AMBIENT) {
    if (hitRecord.isSphere) {
      total = total + hitRecord.sphere.material.ambient*lightColor;
    } else {
      total = total + hitRecord.triangle.material.ambient*lightColor;
    }
  }

  //DIFFUSE!
  float ln = lightDirectionVec.dot(n);
  float diffPos = max(0.0f, ln);
  //SPECULAR
  Vector r = n*2*ln - lightDirectionVec;
  r = r.normalize();
  float specPos;
  Vector v;
    v = rayDirection*(-1);

  v = v.normalize();
  if (hitRecord.isSphere) {
    specPos = pow(max(0.0f, r.dot(v)), sphere.material.exp);
    diffuse = sphere.material.diffuse*lightColor;
    specular = sphere.material.specular*lightColor;
  } else {
    specPos = pow(max(0.0f, r.dot(v)), triangle.material.exp);
    diffuse = triangle.material.diffuse*lightColor;
    specular = triangle.material.specular*lightColor;              
  }
  diffuse = diffuse.scale(diffPos);
  specular = specular.scale(specPos);
  total = total + diffuse + specular; 
  return total;
}
