#include <math.h>
#include <iostream>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <cmath>
#include <time.h>

#include "CImg.h"
#include "Camera.h"
#include "Tracer.h"
#include "Canvas.h"
#include "Coord.h"
#include "objParse.cpp"
#include "SaveImg.cpp"
#include "Sphere.h"
#include "Triangle.h"
#include "Light.h"

using namespace std;

//************************
// GLOBAL VARIABLES 
//************************
	vector<Shape*> all_shapes;
	vector<Triangle> objects; //things to push onto for obj parse
	vector<Light> lights;
	Material last_material = Material(Color(0,0,0), Color(0,0,0), Color(0,0,0), 0, Color(0,0,0)); //intialize to black so there's no garbage
	Coord camEye = Coord(0,0,0);
	Coord camLL = Coord(-1,-1,-1);
	Coord camLR = Coord(1,-1,-1);
	Coord camUL = Coord(-1,1,-1);
	Coord camUR = Coord(1,1,-1); //THE DEFAULT VALUES are bc im too lazy to enter thru command line
	int canvasX = 10; //CHANGE THESE!
	int canvasY = 10; //CHANGE THESE!


// Main render loop
void render() {
	//SET UP CAVAS
	Canvas canvas = Canvas(canvasX, canvasY);

	// //SET UP IMAGE
	cimg_library::CImg<float> img = createImg(canvasX, canvasY); // Creates Img

	// //SET UP TRACER
	Tracer tracer = Tracer(all_shapes);

	// //SET UP CAMERA through command line
	Camera camera = Camera(camEye, camLL, camUL, camLR, camUR);

	//RENDER LOOP
	while(canvas.getSample(&canvas.currSample)) {
		cout << canvas.currSample << endl;
		Ray ray = camera.shootRay(canvas.currSample);
		cout << "THE RAY AT " << canvas.currSample << " IS " << ray << "\n";
		if (tracer.hit(ray)) {
			cout << "hit at " << canvas.currSample << endl;
		    Color color = tracer.trace(ray);
		    editPixel(&img, canvas.currSample, color); //writes to the image			
		}
	}

	saveImg(img); // Saving image to file result.png
	img.display(); // Displaying image
};

//To put command line parsings here
void commandLine(int argc, char *argv[]) {
	for (int i = 1; i < argc; ++i) {
	    if (i < argc && strcmp(argv[i], "-cam") == 0) {
	      //cam ex ey ez llx lly llz lrx lry lrz ulx uly ulz urx ury urz
	      camEye = Coord(strtof(argv[i+1], NULL), strtof(argv[i+2], NULL), strtof(argv[i+3], NULL));
	      camLL = Coord(strtof(argv[i+4], NULL), strtof(argv[i+5], NULL), strtof(argv[i+6], NULL));
	      camLR = Coord(strtof(argv[i+7], NULL), strtof(argv[i+8], NULL), strtof(argv[i+9], NULL));
	      camUL = Coord(strtof(argv[i+10], NULL), strtof(argv[i+11], NULL), strtof(argv[i+12], NULL));
	      camUR = Coord(strtof(argv[i+13], NULL), strtof(argv[i+14], NULL), strtof(argv[i+15], NULL));
	      i += 15;
	    }
	    if (i < argc && strcmp(argv[i], "-sph") == 0) {
	      Coord c = Coord(strtof(argv[i+1], NULL), strtof(argv[i+2], NULL), strtof(argv[i+3], NULL));
	      Sphere * sph = new Sphere(c, strtof(argv[i+4], NULL), last_material);
	      all_shapes.push_back(sph);
	      i += 4;
	      cout << "entered sphere" << endl;
	    }
	    if (i < argc && strcmp(argv[i], "-tri") == 0) {
	      Coord a = Coord(strtof(argv[i+1], NULL), strtof(argv[i+2], NULL), strtof(argv[i+3], NULL));	
	      Coord b = Coord(strtof(argv[i+4], NULL), strtof(argv[i+5], NULL), strtof(argv[i+6], NULL));	
	      Coord c = Coord(strtof(argv[i+7], NULL), strtof(argv[i+8], NULL), strtof(argv[i+9], NULL));	
	      Triangle * tri = new Triangle(a, b, c, last_material);
	      all_shapes.push_back(tri);
	      i += 9;
	      cout << "entered triangle" << endl;
	    }
	    if (i < argc && strcmp(argv[i], "-obj") == 0) {
	    	objParse(argv[i+1], &objects);
	    	for (int i = 0; i < objects.size(); i++) {
	    		Triangle * objtri = new Triangle(objects[i].point1, objects[i].point2, objects[i].point3, last_material);
	    		all_shapes.push_back(objtri);	  
	    	}
	    	//hacky fix to deal w/ shape class, if slow fix later ^ 
	      i += 1;
	    }
	    if (i < argc && strcmp(argv[i], "-ltp") == 0) {
	    	//ltp px py pz r g b falloff
	      Coord pl = Coord(strtof(argv[i+1], NULL), strtof(argv[i+2], NULL), strtof(argv[i+3], NULL));
	      Color pl_c = Color(strtof(argv[i+4], NULL), strtof(argv[i+5], NULL), strtof(argv[i+6], NULL));
	      lights.push_back(Light(pl, pl_c, 2, strtof(argv[i+7], NULL)));
	      i += 7;
	    }
	    if (i < argc && strcmp(argv[i], "-ltd") == 0) {
	      Coord dl = Coord(strtof(argv[i+1], NULL), strtof(argv[i+2], NULL), strtof(argv[i+3], NULL));
	      Color dl_c = Color(strtof(argv[i+4], NULL), strtof(argv[i+5], NULL), strtof(argv[i+6], NULL));
	      lights.push_back(Light(dl, dl_c, 1));
	      i += 6;
	    }
	    if (i < argc && strcmp(argv[i], "-lta") == 0) {
	      Coord al = Coord(0,0,0); //lol
	      Color al_c = Color(strtof(argv[i+1], NULL), strtof(argv[i+2], NULL), strtof(argv[i+3], NULL));
	      lights.push_back(Light(al, al_c, 0));
	      i += 3;
	    }
	    if (i < argc && strcmp(argv[i], "-mat") == 0) {
	      Color ka = Color(strtof(argv[i+1], NULL), strtof(argv[i+2], NULL), strtof(argv[i+3], NULL));
	      Color kd = Color(strtof(argv[i+4], NULL), strtof(argv[i+6], NULL), strtof(argv[i+6], NULL));
	      Color ks = Color(strtof(argv[i+7], NULL), strtof(argv[i+8], NULL), strtof(argv[i+9], NULL));
	      Color kr = Color(strtof(argv[i+11], NULL), strtof(argv[i+12], NULL), strtof(argv[i+13], NULL));
	      last_material = Material(ka, kd, ks, strtof(argv[i+10], NULL), kr);
	      i += 13;
	    }    

	    //TO DO: TRANSFORMATIONS
	    else { //error handling per last pg in spec
	    	cerr << "Bad command line input" << endl;
	    }
	}
}

int main (int argc, char *argv[]) {
	//TODO: create transformation matrices (library?)	
  commandLine(argc, argv);
  	//Sphere s = Sphere(Coord(1, 1, 1), 2, last_material);
  	//all_shapes.push_back(s);

  	Sphere q = Sphere(Coord(1, 1, 1), 2, last_material);
  	// cout << "SHAPE!!! " << q << endl;
  Coord coord = Coord(1,1,1);
  Color color = Color(1,1,1);
  Material material =  Material(color, color, color, 1.0, color);
  Triangle * objtri = new Triangle(coord, coord, coord, material);
  all_shapes.push_back(objtri);   
	cout << "These are the current shapes:" << endl;
	cout << "all shapes size is" << all_shapes.size() << endl;
	for (int i = 0; i < all_shapes.size(); i++) {
		cout << "BING" << endl;
		cout << *(all_shapes[i]) << endl;
	}

  cout << "rendering..." << endl;
  render();
	// cimg_library::CImg<float> img = createImg(2, 2); // Creates a 2x2 Img
  // Sample sample = Sample (0,0); // Instantiating a pixel @ 0,0 (origin @ top-left)
  // Sample sample2 = Sample (1, 1); // Instantiating a pixel @ 1,1 (thus bottom-right)
  // Color imgCol1 = Color(255,0,255);
  // Color imgCol2 = Color(0, 255, 255);
  // editPixel(&img, sample, imgCol1); // Setting 0,0 to have be magenta.
  // editPixel(&img, sample2, imgCol2); // Setting 1,1 to be cyan.
  // saveImg(img); // Saving image to file result.png
  // img.display(); // Displaying image
	//
  return 0;
}
