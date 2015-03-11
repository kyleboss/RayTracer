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
	vector<Shapes> all_shapes;
	vector<Triangle> objects; //things to push onto for obj parse
	vector<Light> lights;
	Material last_material = Material(Color(0,0,0), Color(0,0,0), Color(0,0,0), 0, Color(0,0,0)); //intialize to black so there's no garbage
	Coord camEye;
	Coord camLL;
	Coord camLR;
	Coord camUL;
	Coord camUR;
	int canvasX = 3; //CHANGE THESE!
	int canvasY = 3; //CHANGE THESE!


// Main render loop
void render() {
	//SET UP CAVAS
	Canvas canvas = Canvas(canvasX, canvasY);

	// //SET UP IMAGE
	cimg_library::CImg<float> img = createImg(canvasX, canvasY); // Creates Img

	// //SET UP TRACER
	Tracer tracer = Tracer(all_shapes);

	// //SET UP CAMERA through command line
	Camera camera = Camera(eyeEye, camLL, camUL, camLR, camUR);

	//RENDER LOOP
	while(canvas.getSample(&canvas.currSample)) {
		cout << canvas.currSample << endl;
		Ray ray = camera.shootRay(canvas.currSample);
		//Color color = tracer.trace(ray);
		//editPixel(&img, canvas.currSample, color); //writes to the image
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
	      all_shapes.push_back(Sphere(c, strtof(argv[i+4], NULL)));
	      i += 4;
	    }
	    if (i < argc && strcmp(argv[i], "-tri") == 0) {
	      Coord a = Coord(strtof(argv[i+1], NULL), strtof(argv[i+2], NULL), strtof(argv[i+3], NULL));	
	      Coord b = Coord(strtof(argv[i+4], NULL), strtof(argv[i+5], NULL), strtof(argv[i+6], NULL));	
	      Coord c = Coord(strtof(argv[i+7], NULL), strtof(argv[i+8], NULL), strtof(argv[i+9], NULL));	
	      all_shapes.push_back(Triangle(a, b, c));
	      i += 9;
	    }
	    if (i < argc && strcmp(argv[i], "-obj") == 0) {
	    	objParse(argv[i+1], &objects);
	    	for (int i = 0; i < objects.size(); i++)
	    		all_shapes.push_back(objects[i]);
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
	      last_material = Material(ka, kd, ks, strtof(argv[i+10], NULL), kr));
	      i += 13;
	    }    
	    //TO DO: TRANSFORMATIONS
	    else { //error handling per last pg in spec
	    	cerr << "Bad command line input" << endl;
	    	i += 1;
	    }
	}
}

int main (int argc, char *argv[]) {
	//TODO: create transformation matrices (library?)	
  commandLine(argc, argv);


	cout << "These are the current shapes: " << endl;
	for (int i = 0; i < all_shapes.size(); i++) {
		cout << all_shapes[i] << endl;
	}
<<<<<<< HEAD


=======
  Color color = Color(255, 0, 255);
  Material material = Material(color, color, color, 1, color);
  Coord coord = Coord(1,1,1);
  Sphere sphere = Sphere(coord, 1, material);
  cout << sphere;
>>>>>>> origin/master
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
