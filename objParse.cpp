
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <cmath>
#include <time.h>
#include <math.h>
#include "Coord.h"


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





//****************************************************
// main so i debug easy
//****************************************************
int main(int argc, char *argv[]) {
  vector<Coord> vertices;
          vector<double> faces, normals, textures;

  objParse(argv[1], vertices, faces, normals, textures);
  return 0;
}