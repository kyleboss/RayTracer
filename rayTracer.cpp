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
#include "Coord.h"
#include "Camera.h"
#include "Light.h"
#include "MaterialProps.h"
#include "Triangle.h"
#include "Ray.h"
// #include "objParse.cpp"


using namespace std;

void read_line(istream& stream, vector<Coord> vertices, vector<double> faces, vector<double> normals, vector<double> textures) {
  string line;
  getline(stream, line); //line is relevant data
  //vertices
  const char *l = line.c_str();
  if (strncmp(l, "v ", 2) == 0) {
    cout << "VERTEX! " + line << endl;

    string buf;
    stringstream ss(line);

    vector<string> tokens;

    while (ss >> buf) {
      tokens.push_back(buf);
    }
    for (int i = 0; i < tokens.size(); i += 4) {
      //get rid of Vs, load 3 points as a coordinate 
      vertices.push_back(Coord(stod(tokens[i+1]), stod(tokens[i+2]), stod(tokens[i+3])));
    }

    //take the 3 things (split by space)
    //add them to a vertex class

  }
  else if (strncmp(l, "f ", 2) == 0) {
    //cout << "FACE! " + line << endl;
    //load the 3 vertex indices as a triangle
  }
  else if (strncmp(l, "vt ", 3) == 0) {
    //cout << "TEXTURE! " + line << endl;
  }
  else if (strncmp(l, "vn ", 3) == 0) {
    //cout << "NORMAL! " + line << endl;
  }


  //cout << line << endl;
}


//implies that obj filename was parsed and passed in, given WITH quotes, in same directory
void objParse(char * filename, vector<Coord> vertices, vector<double> faces, vector<double> normals, vector<double> textures){
  ifstream objFile(filename);
  if (objFile.is_open()) {
    while (objFile.good()) {
      read_line(objFile, vertices, faces, normals, textures);
    }
    objFile.close();
  }
  else {
    cout << "NOTE: Can not open .obj file." << endl;
  }
}

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
  vector<Coord> vertices;
          vector<double> faces, normals, textures;

  objParse(argv[1], vertices, faces, normals, textures);
  return 0;
}