
#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>

#ifdef _WIN32
#include <windows.h>
#else
#include <sys/time.h>
#endif

#ifdef OSX
#include <GLUT/glut.h>
#include <OpenGL/glu.h>
#else
#include <GL/glut.h>
#include <GL/glu.h>
#endif

#include <time.h>
#include <math.h>



#define PI 3.14159265  // Should be used from mathlib
inline float sqr(float x) { return x*x; }
const int AMBIENT = 0;
const int DIRECTIONAL = 1;
const int POINT = 2;
using namespace std;

//****************************************************
// Some Classes
//****************************************************

// class Viewport;

// class Viewport {
//   public:
//     int w, h; // width and height
// };


//****************************************************
// Global Variables
//****************************************************
// Viewport  viewport;

// typedef struct {
//   float val1;
//   float val2;
//   float val3;
//   void Set(float v1, float v2, float v3){val1=v1, val2=v2, val3=v3;}
//   float length(){return sqrt(pow(val1,2)+pow(val2,2)+pow(val3,2));}
//   void normalize(){
//     float length = this->length();
//     this->val1 = this->val1/length;
//     this->val2 = this->val2/length;
//     this->val3 = this->val3/length;
//   }
//   void scale(float scalar){
//     this->val1 = scalar*val1;
//     this->val2 = scalar*val2;
//     this->val3 = scalar*val3;
//   }
//   void flip(){
//     this->val1 = -val1;
//     this->val2 = -val2;
//     this->val3 = -val3;
//   }
// } Vec;

// float dotProduct(Vec vec1, Vec vec2) {
//   return vec1.val1*vec2.val1 + vec1.val2*vec2.val2 + vec1.val3*vec2.val3;
// }

// Vec mul(Vec vec1, Vec vec2) {
//   Vec mulVec;
//   float val1 = vec1.val1*vec2.val1;
//   float val2 = vec1.val2*vec2.val2;
//   float val3 = vec1.val3*vec2.val3;
//   mulVec.Set(val1, val2, val3);
//   return mulVec;
// }

// Vec add(Vec vec1, Vec vec2, Vec vec3) {
//   Vec addVec;
//   float val1 = vec1.val1+vec2.val1+vec3.val1;
//   float val2 = vec1.val2+vec2.val2+vec3.val2;
//   float val3 = vec1.val3+vec2.val3+vec3.val3;
//   addVec.Set(val1, val2, val3);
//   return addVec;
// }

// Vec sub(Vec vec1, Vec vec2) {
//   Vec subVec;
//   float val1 = vec1.val1-vec2.val1;
//   float val2 = vec1.val2-vec2.val2;
//   float val3 = vec1.val3-vec2.val3;
//   subVec.Set(val1, val2, val3);
//   return subVec;
// }

// typedef struct {
//   Vec color;
//   Vec pos;
//   void Set(Vec setColor, Vec setPos){color=setColor, pos=setPos;}
// } Light;

// Vec ka;
// Vec kd;
// Vec ks;
// Vec v;
// int numDl = 0;
// int numPl = 0;
// float rv = 1;
// int toon = 0;
// int saveImg = 0;
// char fileName[] = "as1.bmp";
// int width = 400;
// int height = 400;
// FILE *filePtr;
// unsigned char *image = NULL;
// unsigned char bmppad[3] = {0,0,0};
// int filesize = 54 + 3*width*height;  //w is your image width, h is image height, both int

// Light dl0, dl1, dl2, dl3, dl4, pl0, pl1, pl2, pl3, pl4;
// Light lights[] = {dl0, dl1, dl2, dl3, dl4};
// Light pl[] = {pl0, pl1, pl2, pl3, pl4};

//****************************************************
// Simple init function
//****************************************************
// void initScene(int argc, char *argv[]){
//   for (int i = 1; i < argc; ++i) {
//     if(i < argc && strcmp(argv[i], "-ka") == 0) {
//       float r = strtof(argv[i+1], NULL);
//       float g = strtof(argv[i+2], NULL);
//       float b = strtof(argv[i+3], NULL);
//       ka.Set(r,g,b);
//       //GLfloat ambient[] = {r,g,b,1};
//       //glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
//       i += 3;
//     }
//     if(i < argc && strcmp(argv[i], "-kd") == 0) {
//       float r = strtof(argv[i+1], NULL);
//       float g = strtof(argv[i+2], NULL);
//       float b = strtof(argv[i+3], NULL);
//       kd.Set(r,g,b);
//       //GLfloat diffuse[] = {r,g,b,1};
//       //glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
//       i += 3;
//     }
//     if(i < argc && strcmp(argv[i], "-ks") == 0) {
//       float r = strtof(argv[i+1], NULL);
//       float g = strtof(argv[i+2], NULL);
//       float b = strtof(argv[i+3], NULL);
//       ks.Set(r,g,b);
//       //GLfloat specular[] = {r,g,b,1};
//       //glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
//       i += 3;
//     }
//     if(i < argc && strcmp(argv[i], "-sp") == 0) {
//       rv = strtof(argv[i+1], NULL);
//       //glMaterialf(GL_FRONT, GL_SHININESS, rv);
//       i += 1;
//     }
//     if(i < argc && strcmp(argv[i], "-pl") == 0) {
//       float x = strtof(argv[i+1], NULL);
//       float y = strtof(argv[i+2], NULL);
//       float z = strtof(argv[i+3], NULL);
//       float r = strtof(argv[i+4], NULL);
//       float g = strtof(argv[i+5], NULL);
//       float b = strtof(argv[i+6], NULL);
//       Vec lightColor;
//       Vec lightPos;
//       lightColor.Set(r,g,b);
//       lightPos.Set(x,y,z);
//       pl[numPl].Set(lightColor, lightPos);
//       numPl += 1;
//       i += 6;
//     }
//     if(i < argc && strcmp(argv[i], "-dl") == 0) {
//       float x = strtof(argv[i+1], NULL);
//       float y = strtof(argv[i+2], NULL);
//       float z = strtof(argv[i+3], NULL);
//       float r = strtof(argv[i+4], NULL);
//       float g = strtof(argv[i+5], NULL);
//       float b = strtof(argv[i+6], NULL);
//       Vec lightColor;
//       Vec lightPos;
//       lightColor.Set(r,g,b);
//       lightPos.Set(x,y,z);
//       dl[numDl].Set(lightColor, lightPos);
//       numDl += 1;
//       i += 6;
//     }
//     if(i < argc && strcmp(argv[i], "-t") == 0) {
//       toon = 1;
//       i+=1;
//     }
//     if(i < argc && strcmp(argv[i], "-s") == 0) {
//       saveImg = 1;
//       image = new unsigned char[3*width*height*sizeof(char)];
//       glPixelStorei(GL_PACK_SWAP_BYTES,1);

//       if( image ) {
//         free( image );
//       }
//       image = (unsigned char *)malloc(3*width*height);
//       memset(image,0,sizeof(image));
//       unsigned char bmpfileheader[14] = {'B','M', 0,0,0,0, 0,0, 0,0, 54,0,0,0};
//       unsigned char bmpinfoheader[40] = {40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0, 24,0};
//       unsigned char bmppad[3] = {0,0,0};
//       bmpfileheader[ 2] = (unsigned char)(filesize    );
//       bmpfileheader[ 3] = (unsigned char)(filesize>> 8);
//       bmpfileheader[ 4] = (unsigned char)(filesize>>16);
//       bmpfileheader[ 5] = (unsigned char)(filesize>>24);

//       bmpinfoheader[ 4] = (unsigned char)(       width    );
//       bmpinfoheader[ 5] = (unsigned char)(       width>> 8);
//       bmpinfoheader[ 6] = (unsigned char)(       width>>16);
//       bmpinfoheader[ 7] = (unsigned char)(       width>>24);
//       bmpinfoheader[ 8] = (unsigned char)(       height    );
//       bmpinfoheader[ 9] = (unsigned char)(       height>> 8);
//       bmpinfoheader[10] = (unsigned char)(       height>>16);
//       bmpinfoheader[11] = (unsigned char)(       height>>24);
//       filePtr = fopen("img.bmp","wb");
//       fwrite(bmpfileheader,1,14,filePtr);
//       fwrite(bmpinfoheader,1,40,filePtr);
//       i+=1;
//     }
//   }
// }


//****************************************************
// reshape viewport if the window is resized
//****************************************************
// void myReshape(int w, int h) {
//   viewport.w = w;
//   viewport.h = h;

//   glViewport (0,0,viewport.w,viewport.h);
//   glMatrixMode(GL_PROJECTION);
//   glLoadIdentity();
//   gluOrtho2D(0, viewport.w, 0, viewport.h);

// }


//****************************************************
// A routine to set a pixel by drawing a GL point.  This is not a
// general purpose routine as it assumes a lot of stuff specific to
// this example.
//****************************************************

// void setPixel(int x, int y, int z, GLfloat r, GLfloat g, GLfloat b) {
//   glColor3f(r, g, b);
//   glVertex2f(x + 0.5, y + 0.5);   // The 0.5 is to target pixel
//   glNormal3f(0,0,z);
//   // centers 
//   // Note: Need to check for gap
//   // bug on inst machines.
// }

//****************************************************
// Draw a filled circle.  
//****************************************************


Color shadeCircle(HitRecord hitRecord, Vector w) {
  Sphere sphere = hitRecord.sphere;
  float x = hitRecord.intersection.x;
  float y = hitRecord.intersection.y;
  // Draw inner circle
  // glBegin(GL_POINTS);

  // We could eliminate wasted work by only looping over the pixels
  // inside the sphere's radius.  But the example is more clear this
  // way.  In general drawing an object by loopig over the whole
  // screen is wasteful.

  // int i,j;  // Pixel indices

  // int minI = max(0,(int)floor(centerX-radius));
  // int maxI = min(viewport.w-1,(int)ceil(centerX+radius));

  // int minJ = max(0,(int)floor(centerY-radius));
  // int maxJ = min(viewport.h-1,(int)ceil(centerY+radius));



  // for (i=0;i<viewport.w;i++) {
  //   for (j=0;j<viewport.h;j++) {

      // Location of the center of pixel relative to center of sphere
      x = (x+0.5-sphere.center.x);
      y = (y+0.5-sphere.center.y);
      // Vector v = Vector(0,0,1); // ??

      float dist = sqrt(sqr(x) + sqr(y));

      if (dist<=sphere.r) {

        // This is the front-facing Z coordinate
        float z = sqrt(sphere.r*sphere.r-dist*dist);
        
        Color total(0,0,0); //treat as color
        Vector norm(x,y,z); //normal: position vector
        norm = norm.normalize();

        for(std::vector<Light *>::iterator itor=(Light::lights).begin(); itor!=Light::lights.end(); ++itor)
        {
          Coord normLightCoord = (*itor)->location;
          Vector normLight = Vector(normLightCoord.x, normLightCoord.y, normLightCoord.z);
          if ((*itor)->type == DIRECTIONAL) {
            normLight = normLight*(-1);
          } else if ((*itor)->type == POINT) {
            normLight = norm-normLight;
          }
          normLight = normLight.normalize();
          float ln = normLight.dot(norm);
          float diffPos = max(0.0f, ln); //max(l.n, 0)
          Vector r = norm;
          r=r*(2*ln);
          r=r-normLight;
          r=r.normalize();
          float specPos = pow(max(0.0f, r.dot(w)), sphere.material.exp); // CHECK v
          Color ambient = sphere.material.ambient*(*itor)->color;
          Color diffuse = sphere.material.diffuse*(*itor)->color;
          diffuse.scale(diffPos);
          Color specular = sphere.material.specular*(*itor)->color;
          specular.scale(specPos);
          Color total = total+ambient+diffuse+specular;
          return total;
        }

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

       // if (toon) { //WOW COOL IF STATEMENTS YEAH
       //    if (total.val1 < 0.35) {
       //      total.val1 = 0.2;
       //    }
       //    if (total.val2 < 0.35) {
       //      total.val2 = 0.2;
       //    }
       //    if (total.val3 < 0.35) {
       //      total.val3 = 0.2;
       //    }          
       //    if (total.val1 < 0.392 && total.val1 >= 0.15) {
       //      total.val1 = 0.196;
       //    }
       //    if (total.val2 < 0.392 && total.val2 >= 0.15) {
       //      total.val2 = 0.196;
       //    }
       //    if (total.val3 < 0.392 && total.val3 >= 0.15) {
       //      total.val3 = 0.196;
       //    }          
       //    if (total.val1 < 0.784 && total.val1 >= 0.35) {
       //      total.val1 = 0.684;
       //    }
       //    if (total.val2 < 0.784 && total.val2 >= 0.35) {
       //      total.val2 = 0.684;
       //    }
       //    if (total.val3 < 0.784 && total.val3 >= 0.35) {
       //      total.val3 = 0.684;
       //    }  
       //    if (total.val1 >= 0.784) {
       //      total.val1 = 0.94;
       //    }
       //    if (total.val2 >= 0.784) {
       //      total.val2 = 0.94;
       //    }
       //    if (total.val3 >= 0.784) {
       //      total.val3 = 0.94;
       //    }  
       //  }
        
        // setPixel(i, j, z, total.val1, total.val2, total.val3);

        // This is amusing, but it assumes negative color values are treated reasonably.
        // setPixel(i,j, x/radius, y/radius, z/radius );
      }


  //   }
  // }


  // glEnd();
}
//****************************************************
// function that does the actual drawing of stuff
//***************************************************
// void myDisplay() {
//   glClear(GL_COLOR_BUFFER_BIT);       // clear the color buffer

//   glMatrixMode(GL_MODELVIEW);             // indicate we are specifying camera transformations
//   glLoadIdentity();               // make sure transformation is "zero'd"


//   // Start drawing

//   circle(viewport.w / 2.0 , viewport.h / 2.0 , min(viewport.w, viewport.h) * 0.45);
//   if (saveImg) {
//     glReadBuffer(GL_BACK_RIGHT);
//     glReadPixels(0,0,width,height,GL_BGR,GL_UNSIGNED_BYTE,image);
//     for (int j=0; j<height; j++) {
//       for (int i=0;i<width; i++) {
//         fputc(image[3*j*width+3*i+0],filePtr);
//         fputc(image[3*j*width+3*i+1],filePtr);
//         fputc(image[3*j*width+3*i+2],filePtr);
//       }
//     }
//     fclose(filePtr);
//     delete [] image;
//   }
//   glFlush();
//   glutSwapBuffers();          // swap buffers (we earlier set double buffer)
// }


// void handle(unsigned char key, int x, int y) {
//   switch (key) {
//     case 32: //space
//       exit(0);
//       break;
//   }
//   glutPostRedisplay();
// }


//****************************************************
// the usual stuff, nothing exciting here
//****************************************************
// int main(int argc, char *argv[]) {
//   //This initializes glut
//   glutInit(&argc, argv);
//   //This tells glut to use a double-buffered window with red, green, and blue channels 
//   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

//   // Initalize theviewport size
//   viewport.w = 400;
//   viewport.h = 400;

//   //The size and position of the window
//   glutInitWindowSize(viewport.w, viewport.h);
//   glutInitWindowPosition(0,0);
//   glutCreateWindow(argv[0]);
//   v.Set(0, 0, 1);
//   initScene(argc, argv);              // quick function to set up scene
//   glutDisplayFunc(myDisplay);       // function to run when its time to draw something
//   glutReshapeFunc(myReshape);       // function to run when the window gets resized
//   glutKeyboardFunc(handle); //exit on space
//   glutMainLoop();             // infinite loop that will keep drawing and resizing
//   // and whatever else

//   return 0;
// }