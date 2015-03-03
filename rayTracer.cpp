#include <math.h>
#include <iostream>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <cmath>
#include <time.h>
#include "Color.h"
#include "Canvas.h"
#include "Camera.h"
#include "Light.h"
#include "MaterialProps.h"
#include "Triangle.h"
#include "Ray.h"
#include "objParse.cpp"
#include "CImg.h"


using namespace std;
using namespace cimg_library;

//To put command line parsings here
void commandLine(int argc, char *argv[]) {
	for (int i = 1; i < argc; ++i) {
	    if(i < argc && strcmp(argv[i], "-obj") == 0) {
	    	vector<double> vertices, faces, normals, textures;
	    	objParse(argv[i+1], vertices, faces, normals, textures);
	      	i += 1;
	    }
	    else { //error handling per last pg in spec
	    	stderr << "You fucked up";
	    }
	}
}


int main (int argc, char *argv[]) {
  commandLine(argc, argv);
  Canvas canvas = Canvas(400.0, 40.0);
  Camera cam = Camera(1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0);
  Light light = Light (1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
  MaterialProps visObj = MaterialProps(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12);
  Triangle tri = Triangle(1, 2, 3, 4, 5, 6, 7, 8, 9);
  cout << light.color.r;
  cout << "rendering..." << endl;
  return 0;
}