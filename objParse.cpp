#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <cmath>
#include <time.h>
#include <math.h>

using namespace std;

#include "Coord.h"
#include "Triangle.h"

//Takes in an obj file, fills the passed in obj vector of triangles in return.

void read_line(istream& stream, vector<Triangle> * objects, vector<Coord> * temp_vertices, Matrix * transMatrix) {
  string line;
  getline(stream, line); //line is relevant data
  //vertices  

  const char *l = line.c_str();
  if (strncmp(l, "v ", 2) == 0) {
    //cout << "VERTEX! " + line << endl;

    string buf;
    stringstream ss(line);

    vector<string> tokens;

    while (ss >> buf) {
      tokens.push_back(buf);
    }
    for (int i = 0; i < tokens.size(); i+=4) { //TO BE i+=4 CHANGE BACK
      //get rid of Vs, load 3 points as a coordinate
      //cout << "YO!!!!!!!!!!!!!!! " << tokens.at(i) << endl;
      string a = tokens[i+1];
      string b = tokens[i+2];
      string c = tokens[i+3];
      //Coord temp_coord = Coord(stof(a, NULL), stof(b, NULL), stof(c, NULL));
      Coord temp_coord(stof(tokens[i+1], NULL), stof(tokens[i+2], NULL), stof(tokens[i+3], NULL));
      //cout << "COORD IS " << temp_coord << endl;
      temp_vertices->push_back(temp_coord);
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
      //cout << "HI WE'RE HERE" << endl;
      //break each token by its slash
      string v1 = tokens[i+1];
      string v2 = tokens[i+2];
      string v3 = tokens[i+3];
      //cout << "V1 IS " << v1 << "V2 IS " << v2 << "V3 IS " << v3 << endl; //works
      int v1i = stoi(v1.substr(0, v1.find(slash))) - 1; //v1 is f v1, aka the index of the vertex
      int v2i = stoi(v2.substr(0, v2.find(slash))) - 1;
      int v3i = stoi(v3.substr(0, v3.find(slash))) - 1; //-1 bc 1 indexed
      //cout << "V1i IS " << v1i << " V2i IS " << v2i << " V3i IS " << v3i << endl;
      //SUB ONE FROM INDEX

      //deal with other /'s later
      //find vertices, add them to objects
      Coord a = (*temp_vertices)[v1i];
      Coord b = (*temp_vertices)[v2i];
      Coord c = (*temp_vertices)[v3i];
      Triangle tri(a, b, c, *transMatrix);
      objects->push_back(tri);
      //cout << "pushed triangle " << tri << endl;

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
void objParse(char * filename, vector<Triangle> * objects, Matrix * transMatrix){
  vector<Coord> temp_vertices;
  ifstream objFile(filename);
  if (objFile.is_open()) {
    while (objFile.good()) {
      read_line(objFile, objects, &temp_vertices, transMatrix);
    }
    objFile.close();
  }
  else {
    cout << "NOTE: Can not open .obj file." << endl;
  }
}
