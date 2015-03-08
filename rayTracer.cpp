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

#include "objParse.cpp"
#include "SaveImg.cpp"

using namespace std;

//global variables
vector<Triangle> objects; //things to push onto for obj parse
vector<Sphere> spheres;
Coord camEye;
Coord camLL;
Coord camLR;
Coord camUL;
Coord camUR;

// Main render loop
void render() {
	//SET UP CAVAS
	Canvas canvas = Canvas(2, 2);

	//SET UP IMAGE
	cimg_library::CImg<float> img = createImg(2, 2); // Creates a 2x2 Img

	//SET UP TRACER
	Tracer tracer = Tracer(objects);

	//SET UP CAMERA
	Coord loc = Coord(1, 1, 1);
  	Coord viewDir = Coord(2, 2, 2);
	Camera camera = Camera(loc, 1, viewDir);

	//RENDER LOOP
	while(canvas.getSample(&canvas.currSample)) {
		Ray ray = camera.shootRay(canvas.currSample);
		Color color = tracer.trace(ray);
		editPixel(&img, canvas.currSample, color);
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
	    if (i < argc && strcmp(argv[i], "-obj") == 0) {
	    	objParse(argv[i+1], objects);
	      i += 1;
	    }
	    if (i < argc && strcmp(argv[i], "-sph") == 0) {
	      Coord c = Coord(strtof(argv[i+1], NULL), strtof(argv[i+2], NULL), strtof(argv[i+3], NULL));	
	      spheres.push_back(Sphere(c, strtof(argv[i+4], NULL)));
	      i += 4;
	    }
	    if (i < argc && strcmp(argv[i], "-tri") == 0) {
	      Coord a = Coord(strtof(argv[i+1], NULL), strtof(argv[i+2], NULL), strtof(argv[i+3], NULL));
	      Coord b = Coord(strtof(argv[i+4], NULL), strtof(argv[i+5], NULL), strtof(argv[i+6], NULL));
	      Coord c = Coord(strtof(argv[i+7], NULL), strtof(argv[i+8], NULL), strtof(argv[i+9], NULL));
	      objects.push_back(Triangle(a, b, c));
	      i += 9;
	    }	    
	    else { //error handling per last pg in spec
	    	cerr << "Bad command line input" << endl;
	    }
	}
}

int main (int argc, char *argv[]) {
  commandLine(argc, argv);
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
