
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <cmath>
#include <time.h>
#include <math.h>
#include "Coord.h"
#include "Triangle.h"


using namespace std;

//Takes in an obj file, fills the passed in obj vector of triangles in return.

void read_line(istream& stream, vector<Triangle> objects) {
  string line;
  getline(stream, line); //line is relevant data
  //vertices
  vector<Coord> temp_vertices;

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
      temp_vertices.push_back(Coord(stod(tokens[i+1]), stod(tokens[i+2]), stod(tokens[i+3])));
    }
  }
  else if (strncmp(l, "f ", 2) == 0) {
    //cout << "FACE! " + line << endl;
    string buf;
    stringstream ss(line);

    vector<string> tokens;

    while (ss >> buf) {
      tokens.push_back(buf);
    }

    string slash = "/";

    for (int i = 0; i < tokens.size(); i += 4) {
      //break each token by its slash
      string v1 = tokens[i+1];
      string v2 = tokens[i+2];
      string v3 = tokens[i+3];

      int v1i = stoi(v1.substr(0, v1.find(slash))) - 1; //v1 is f v1, aka the index of the vertex
      int v2i = stoi(v2.substr(0, v2.find(slash))) - 1;
      int v3i = stoi(v3.substr(0, v3.find(slash))) - 1; //-1 bc 1 indexed
      //deal with other /'s later
      //find vertices, add them to objects
      objects.push_back(Triangle(temp_vertices[v1i], temp_vertices[v2i], temp_vertices[v3i]));
    }
  }
  else if (strncmp(l, "vt ", 3) == 0) {
    //cout << "TEXTURE! " + line << endl;
    //TO LOAD WHEN I DO TEXTURE MAPPING
  }
  //note: add normals if needed, but probably not
  //cout << line << endl;
}


//implies that obj filename was parsed and passed in, given WITH quotes, in same directory
void objParse(char * filename, vector<Triangle> objects){
  ifstream objFile(filename);
  if (objFile.is_open()) {
    while (objFile.good()) {
      read_line(objFile, objects);
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
// int main(int argc, char *argv[]) {
//   vector<Coord> vertices;
//           vector<double> faces, normals, textures;

//   objParse(argv[1], vertices, faces, normals, textures);
//   return 0;
// }