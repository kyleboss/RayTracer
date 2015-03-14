
#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>
#include <time.h>
#include <math.h>


#include "Light.h"

#define PI 3.14159265  // Should be used from mathlib
inline float sqr(float x) { return x*x; }
const int AMBIENT = 0;
const int DIRECTIONAL = 1;
const int POINT = 2;
using namespace std;

//****************************************************
// Draw a filled circle.  
//****************************************************


Color shadeCircle(HitRecord hitRecord, Vector lightDirectionVec, Vector rayDirection, Color lightColor) {
  Sphere sphere = hitRecord.sphere;
  Triangle triangle = hitRecord.triangle;
  float x = hitRecord.intersection.x;
  float y = hitRecord.intersection.y;

      // Location of the center of pixel relative to center of sphere
      Color total = Color(0,0,0);
      // Vector v = Vector(0,0,1); // ??

      // float dist = sqrt(sqr(x) + sqr(y));

      // if (dist<=sphere.r) {

        // This is the front-facing Z coordinate
        // float z = sqrt(sphere.r*sphere.r-dist*dist);
        
        // Vector norm(x,y,z); //normal: position vector
        // norm = norm.normalize();
//         Light(Coord(-2,-2,-2), Color(1, 1, 1), DIRECTIONAL, 1);
//         for(std::vector<Light *>::iterator itor=(Light::lights).begin(); itor!=Light::lights.end(); ++itor)
//         {
//           Vector lightLocationVec = Vector((*itor)->location.x,(*itor)->location.y,(*itor)->location.z);
//           Vector intersectionVec = Vector(hitRecord.intersection.x,hitRecord.intersection.y,hitRecord.intersection.z);
//           Vector lightDirectionVec;
//             if ((*itor)->type == DIRECTIONAL) {
//               lightDirectionVec = lightLocationVec*(-1);
//             } else if ((*itor)->type == POINT) {
//               lightDirectionVec = lightLocationVec-intersectionVec;
//             }
//             lightDirectionVec = lightDirectionVec.normalize();
// /////SHADOW CHECKING

//               else {
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
            


            // cout << "AMBIENT:" << ambient;
            // cout << "DIFFUSE:" << diffuse;
            // cout << "SPECULAR:" << specular;
            // cout << "TOTAL" << total;
            return total;
          // }
        // }

        // for (int k=0; k < numDl; k++) { //loop direction light
        //   Vec normLight = dl[k].pos;
        //   //normLight = sub(norm,normLight);
        //   normLight.flip();
        //   normLight.normalize();
        //   float ln = dotProduct(normLight, norm);
          
        //   float diffPos = max(0.0f, ln); //max(l.n, 0)
          
        //   Vec r;
        //   r.Set(norm.val1, norm.val2, norm.val3); //currently r = n
        //   r.scale(2 * ln);
        //   r = sub(r, normLight); //r is correct
        //   r.normalize();

        //   float specPos = pow(max(0.0f, dotProduct(r, v)), rv);
        //   //dl[k].color = I
        //   // ambient = ka*I; color
        //   Vec ambient = mul(ka, dl[k].color);

        //   //diffuse = kd * I * max(l.n, 0); color
        //   Vec diffuse = mul(kd, dl[k].color);
        //   diffuse.scale(diffPos);

        //   //diffuse = ks * I * max(r.v, 0); color
        //   Vec specular = mul(ks, dl[k].color);
        //   specular.scale(specPos);

        //   Vec subTotal = add(ambient, diffuse, specular);
        //   total.val1 += subTotal.val1;
        //   total.val2 += subTotal.val2;
        //   total.val3 += subTotal.val3;
        // }

        // for (int k=0; k < numPl; k++) { //loop POSITION light
        //   Vec normLight = pl[k].pos;
        //   normLight = sub(normLight, norm);
        //   normLight.normalize();
        //   float ln = dotProduct(normLight, norm);
          
        //   float diffPos = max(0.0f, ln); //max(l.n, 0)
          
        //   Vec r;
        //   r.Set(norm.val1, norm.val2, norm.val3); //currently r = n
        //   r.scale(2 * ln);
        //   r = sub(r, normLight); //r is correct
        //   r.normalize();

        //   float specPos = pow(max(0.0f, dotProduct(r, v)), rv);
        //   //dl[k].color = I
        //   // ambient = ka*I; color
        //   Vec ambient = mul(ka, pl[k].color);

        //   //diffuse = kd * I * max(l.n, 0); color
        //   Vec diffuse = mul(kd, pl[k].color);
        //   diffuse.scale(diffPos);

        //   //diffuse = ks * I * max(r.v, 0); color
        //   Vec specular = mul(ks, pl[k].color);
        //   specular.scale(specPos);

        //   Vec subTotal = add(ambient, diffuse, specular);
        //   total.val1 += subTotal.val1;
        //   total.val2 += subTotal.val2;
        //   total.val3 += subTotal.val3;
        // }
}
