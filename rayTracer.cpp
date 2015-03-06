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
	    if(i < argc && strcmp(argv[i], "-obj") == 0) {
	    	objParse(argv[i+1], objects);
	      i += 1;
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
