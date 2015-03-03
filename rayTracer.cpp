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
#include "objParse.cpp"
#include "Camera.h"
#include "Light.h"
#include "MaterialProps.h"
#include "Ray.h"

using namespace std;

//global variables
vector<Triangle> objects; //things to push onto for obj parse



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
  Coord coord =  Coord(1, 2, 3);
  cout << coord << endl;
  Canvas canvas = Canvas(400.0, 40.0);
  Camera cam = Camera(1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0);
  Light light = Light (1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
  MaterialProps visObj = MaterialProps(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12);
  Triangle tri = Triangle(1, 2, 3, 4, 5, 6, 7, 8, 9);
  Coord c1 = Coord(0, 1, 0);
  Coord c2 = Coord(1, 0, 0);
  Coord c3 = Coord(1, 1, 0);
  Triangle t = Triangle(c1, c2, c3);
  cout << t << endl;
  cout << light.color.r << endl;
  cout << "rendering..." << endl;


  return 0;
}