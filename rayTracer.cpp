#include <math.h>
#include <iostream>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <cmath>
#include <time.h>

int canvasX = 500; //CHANGE THESE!
int canvasY = 500; //CHANGE THESE!
#include "CImg.h"
#include "Camera.h"
#include "Tracer.h"
#include "Canvas.h"
#include "Coord.h"
#include "objParse.cpp"
#include "SaveImg.cpp"
#include "Sphere.h"
#include "Triangle.h"
#include "Matrix.h"
#include "Transform.h"

using namespace std;

//************************
// GLOBAL VARIABLES  
//************************
	vector<Shape*> all_shapes;
	vector<Triangle> objects; //things to push onto for obj parse
	vector<Light> lights;
	Material last_material = Material(Color(0,0,0), Color(0,0,0), Color(0,0,0), 0, Color(0,0,0)); //intialize to black so there's no garbage
	Coord camEye = Coord(0,0,2);
	Coord camLL = Coord(-1,-1,1);
	Coord camLR = Coord(1,-1,1);
	Coord camUL = Coord(-1,1,1);
	Coord camUR = Coord(1,1,1);
	// Matrix transMatrix = Matrix();

 //THE DEFAULT VALUES are bc im too lazy to enter thru command line

// Main render loop
void render() {
	//SET UP CAVAS
	Canvas canvas = Canvas(canvasX, canvasY);

	// //SET UP IMAGE
	cimg_library::CImg<float> img = createImg(canvasX, canvasY); // Creates Img

	// //SET UP TRACER
	Tracer tracer = Tracer(all_shapes);

	// //SET UP CAMERA through command line
	Camera camera = Camera(camEye, camLL, camUL, camLR, camUR, canvasX, canvasY);

	//RENDER LOOP
	while(canvas.getSample(&canvas.currSample)) {
		// cout << canvas.currSample << endl;
		Ray ray = camera.shootRay(canvas.currSample);
		// cout << "THE RAY AT " << canvas.currSample << " IS " << ray << "\n";
		HitRecord hitRecord = tracer.hit(ray);
		if (hitRecord.isHit) {
		    Color color = tracer.trace(hitRecord, lights, ray.direction);
		    //cout << color << " at (" << canvas.currSample.x << " , " << canvas.currSample.y << ")" << endl; 
		    //clipping
		    if (color.r > 1)
		    	color.r = 1;
		    if (color.g > 1)
		    	color.g = 1;
		    if (color.b > 1) 
		    	color.b = 1;
		    editPixel(&img, canvas.currSample, color); //writes to the image			
		}
	}

	saveImg(img); // Saving image to file result.png
	img.display(); // Displaying image
};

//To put command line parsings here
void commandLine(int argc, char *argv[]) { 
	for (int i = 1; i < argc; ++i) {
	    if (i < argc && strcmp(argv[i], "cam") == 0) {
	      //cam ex ey ez llx lly llz lrx lry lrz ulx uly ulz urx ury urz
	      camEye = Coord(strtof(argv[i+1], NULL), strtof(argv[i+2], NULL), strtof(argv[i+3], NULL));
	      camLL = Coord(strtof(argv[i+4], NULL), strtof(argv[i+5], NULL), strtof(argv[i+6], NULL));
	      camLR = Coord(strtof(argv[i+7], NULL), strtof(argv[i+8], NULL), strtof(argv[i+9], NULL));
	      camUL = Coord(strtof(argv[i+10], NULL), strtof(argv[i+11], NULL), strtof(argv[i+12], NULL));
	      camUR = Coord(strtof(argv[i+13], NULL), strtof(argv[i+14], NULL), strtof(argv[i+15], NULL));
	      camEye = Transform::performTransform(camEye);
	      camLL = Transform::performTransform(camLL);
	      camLR = Transform::performTransform(camLR);
	      camUL = Transform::performTransform(camUL);
	      camUR = Transform::performTransform(camUR);
	      i += 15;
	    }
	    else if (i < argc && strcmp(argv[i], "sph") == 0) {
	      Coord c = Coord(strtof(argv[i+1], NULL), strtof(argv[i+2], NULL), strtof(argv[i+3], NULL));
	      c = Transform::performTransform(c);
	      Sphere * sph = new Sphere(c, strtof(argv[i+4], NULL), last_material);
	      all_shapes.push_back(sph);
	      i += 4;
	      cout << "entered sphere" << endl;
	    }
	    else if (i < argc && strcmp(argv[i], "tri") == 0) {
	      Coord a = Coord(strtof(argv[i+1], NULL), strtof(argv[i+2], NULL), strtof(argv[i+3], NULL));	
	      Coord b = Coord(strtof(argv[i+4], NULL), strtof(argv[i+5], NULL), strtof(argv[i+6], NULL));	
	      Coord c = Coord(strtof(argv[i+7], NULL), strtof(argv[i+8], NULL), strtof(argv[i+9], NULL));	
	      a = Transform::performTransform(a);
	      b = Transform::performTransform(b);
	      c = Transform::performTransform(c);
	      Triangle * tri = new Triangle(a, b, c, last_material);
	      all_shapes.push_back(tri);
	      i += 9;
	      cout << "entered triangle" << endl;
	    }
	    else if (i < argc && strcmp(argv[i], "obj") == 0) {
	    	objParse(argv[i+1], &objects);
	    	for (int i = 0; i < objects.size(); i++) {
	    		Triangle * objtri = new Triangle(objects[i].point1, objects[i].point2, objects[i].point3, last_material);
	    		all_shapes.push_back(objtri);	  
	    	}
	    	//hacky fix to deal w/ shape class, if slow fix later ^ 
	      i += 1;
	    }
	    else if (i < argc && strcmp(argv[i], "ltp") == 0) {
	    	//ltp px py pz r g b falloff
	      Coord pl = Coord(strtof(argv[i+1], NULL), strtof(argv[i+2], NULL), strtof(argv[i+3], NULL));
	      Color pl_c = Color(strtof(argv[i+4], NULL), strtof(argv[i+5], NULL), strtof(argv[i+6], NULL));
	      pl = Transform::performTransform(pl);
	      if ((strcmp(argv[i+7], "0") == 0) || (strcmp(argv[i+7], "1") == 0) || (strcmp(argv[i+7], "2") == 0)) {
	      	//if they specified falloff
	      	lights.push_back(Light(pl, pl_c, 2, strtof(argv[i+7], NULL)));
	      	i += 7;
	      }
	      else {
	      	lights.push_back(Light(pl, pl_c, 2, 0));
	      	i+= 6;
	      }
	    }
	    else if (i < argc && strcmp(argv[i], "ltd") == 0) {
	      Coord dl = Coord(strtof(argv[i+1], NULL), strtof(argv[i+2], NULL), strtof(argv[i+3], NULL));
	      Color dl_c = Color(strtof(argv[i+4], NULL), strtof(argv[i+5], NULL), strtof(argv[i+6], NULL));
	      dl = Transform::performTransform(dl);
	      lights.push_back(Light(dl, dl_c, 1));
	      i += 6;
	    }
	    else if (i < argc && strcmp(argv[i], "lta") == 0) {
	      Coord al = Coord(0,0,0); //lol
	      Color al_c = Color(strtof(argv[i+1], NULL), strtof(argv[i+2], NULL), strtof(argv[i+3], NULL));
	      al = Transform::performTransform(al);
	      lights.push_back(Light(al, al_c, 0));
	      i += 3;
	    }
	    else if (i < argc && strcmp(argv[i], "mat") == 0) {
	      Color ka = Color(strtof(argv[i+1], NULL), strtof(argv[i+2], NULL), strtof(argv[i+3], NULL));
	      Color kd = Color(strtof(argv[i+4], NULL), strtof(argv[i+6], NULL), strtof(argv[i+6], NULL));
	      Color ks = Color(strtof(argv[i+7], NULL), strtof(argv[i+8], NULL), strtof(argv[i+9], NULL));
	      Color kr = Color(strtof(argv[i+11], NULL), strtof(argv[i+12], NULL), strtof(argv[i+13], NULL));
	      last_material = Material(ka, kd, ks, strtof(argv[i+10], NULL), kr);
	      i += 13;
	    }    
	    else if (i < argc && strcmp(argv[i], "xft") == 0) {
	 			Transform(TRANSLATION, strtof(argv[i+1], NULL),strtof(argv[i+2], NULL),strtof(argv[i+3], NULL));
	      i += 3;
	    } 
	    else if (i < argc && strcmp(argv[i], "xfr") == 0) {
	 			Transform(ROTATION, strtof(argv[i+1], NULL),strtof(argv[i+2], NULL),strtof(argv[i+3], NULL));
	      i += 3;
	    }
	    else if (i < argc && strcmp(argv[i], "xfs") == 0) {
	 			Transform(SCALE, strtof(argv[i+1], NULL),strtof(argv[i+2], NULL),strtof(argv[i+3], NULL));
	      i += 3;
	    }
	    else if (i < argc && strcmp(argv[i], "xfz") == 0) {
	 			Transform::emptyTransforms();
	      i += 1;
	    }
	    else { //error handling per last pg in spec
	    	cerr << "Bad command line input" << endl;
	    }
	}
}

int main (int argc, char *argv[]) {
  commandLine(argc, argv);
 
//*******************************************
// THIS SETS UP THE SCENE AS ON THE WEBSITE
// pls keep box to avoid merge conflict
// implicit camera as    eye=[ 0.  0.  0.]
	        // LL=[-1. -1. -3.]
	        // LR=[ 1. -1. -3.]
	        // UR=[ 1.  1. -3.]
	        // UL=[-1.  1. -3.]
	        // x, y = 500 x 500
//*******************************************
/*
//Lights 
  Light l = Light(Coord(0.57735027,  -0.57735027, -0.57735027), Color(1, 1, 1), 1);
  Light l1 = Light(Coord(0.57735027,  0.57735027, -0.57735027), Color(0, 0, 1), 1);
  lights.push_back(l);
  lights.push_back(l1);

//Sphere 1
  Color ka = Color(.1, .1, .1);
  Color kd = Color(1, 0, 1); 
  Color ks = Color(1,1,1);
  Color kr = Color(0,0,0);
  Material mat1 = Material(ka, kd, ks, 50, kr);
  Sphere * s1 = new Sphere(Coord(0,0,-20), 3, mat1);

//Sphere 2
  ka = Color(.1, .1, .1);
  kd = Color(1, 1, 0); 
  ks = Color(1,1,1);
  kr = Color(0,0,0);
  Material mat2 = Material(ka, kd, ks, 50, kr);
  Sphere * s2 = new Sphere(Coord(-2,2,-15), 1, mat2);
 
//Sphere 3
  ka = Color(.1, .1, .1);
  kd = Color(0, 1, 1); 
  ks = Color(1,1,1);
  kr = Color(0,0,0);
  Material mat3 = Material(ka, kd, ks, 50, kr);
  //Transform(TRANSLATION, 1, 2, 1);
  Coord c = Coord(-2,-2,-15);
  //c = Transform::performTransform(c);
  //cout << c;
  Sphere * s3 = new Sphere(c, 1, mat3);


  all_shapes.push_back(s1);
  all_shapes.push_back(s2);
  all_shapes.push_back(s3);

//Triangle
  Coord coord = Coord(5,5,-17);
  Coord coord2 = Coord(1,4,-20); 
  Coord coord3 = Coord(6,-1,-20);
  ka = Color(.1, .1, .1);
  kd = Color(.1, .1, .1); 
  ks = Color(1,1,1);
  kr = Color(0,0,0);
  Material mattri =  Material(ka, kd, ks, 50, kr);
  Triangle * tri = new Triangle(coord, coord2, coord3, mattri);
   
  all_shapes.push_back(tri); 
*/
//*********************  
  
  /*Light a = Light(Coord(1, 1, 1), Color(1, 1, 1), 2); //lol not much of a visible change?
  lights.push_back(a); //change from non, lin, quad to your desires  

  Color ka = Color(1,1,1);  
  Color kd = Color(1, 1, 1); 
  Color ks = Color(0,0,0);
  Color kr = Color(0,0,0);
  Material mat1 = Material(ka, kd, ks, 64, kr);
  Sphere * s1 = new Sphere(Coord(0,0,0), 0.65, mat1); 
  all_shapes.push_back(s1);*/




  //Attenuation check
  /*Light none = Light(Coord(2, 2, 2), Color(1, 1, 1), 2, 0);
  Light lin = Light(Coord(2, 2, 2), Color(1, 1, 1), 2, 1);
  Light quad = Light(Coord(2, 2, 2), Color(1, 1, 1), 2, 2); //lol not much of a visible change?
  lights.push_back(none); //change from non, lin, quad to your desires  

  Color ka = Color(.05, .05, .05);
  Color kd = Color(1, 1, 1); 
  Color ks = Color(1,1,1);
  Color kr = Color(0,0,0);
  Material mat1 = Material(ka, kd, ks, 64, kr);
  Sphere * s1 = new Sphere(Coord(0,0,-5), 3.5, mat1); 
  all_shapes.push_back(s1);*/

	cout << "all of the lights" << lights.size() << endl;
	for (int i = 0; i < lights.size(); i++) {
		cout << (lights[i]) << endl;
	}  

	cout << "all shapes size is" << all_shapes.size() << endl;
	for (int i = 0; i < all_shapes.size(); i++) {
		cout << *(all_shapes[i]) << endl;
	}  

  cout << "rendering..." << endl;
  render();
  return 0;
}
