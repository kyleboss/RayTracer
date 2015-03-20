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

void read_line(istream& stream, vector<Triangle> * objects, vector<Coord> * temp_vertices, Matrix * transMatrix, vector<Vector> * temp_normals) {
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
    for (int i = 0; i < tokens.size(); i+=4) { 
      //get rid of Vs, load 3 points as a coordinate
      Coord temp_coord(stof(tokens[i+1], NULL), stof(tokens[i+2], NULL), stof(tokens[i+3], NULL));
      temp_vertices->push_back(temp_coord);
    }
  }
  else if (strncmp(l, "vn ", 3) == 0) {
    //cout << "NORMAL! " + line << endl;
    string buf;
    stringstream ss(line);
    vector<string> tokens;
    while (ss >> buf) {
      tokens.push_back(buf);
    }
    for (int i = 0; i < tokens.size(); i+=4) { 
      //get rid of Vns, load 3 points as a vector
      Vector temp_norm(stof(tokens[i+1], NULL), stof(tokens[i+2], NULL), stof(tokens[i+3], NULL));
      temp_normals->push_back(temp_norm);
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
      //cout << "V1 IS " << v1 << " V2 IS " << v2 << " V3 IS " << v3 << endl; //works
      int v1i = stoi(v1.substr(0, v1.find(slash))) - 1; //v1 is f v1, aka the index of the vertex
      int v2i = stoi(v2.substr(0, v2.find(slash))) - 1;
      int v3i = stoi(v3.substr(0, v3.find(slash))) - 1; //-1 bc 1 indexed
      //cout << "V1i IS " << v1i << " V2i IS " << v2i << " V3i IS " << v3i << endl;
      
      int vn1i = stoi(v1.substr(0, v1.rfind(slash))) - 1; //v1 is f v1, aka the index of the vertex
      int vn2i = stoi(v2.substr(0, v2.rfind(slash))) - 1;
      int vn3i = stoi(v3.substr(0, v3.rfind(slash))) - 1; //-1 bc 1 indexed
      //cout << "Vn1i IS " << v1i << " Vn2i IS " << v2i << " Vn3i IS " << v3i << endl;

      //find vertices, add them to objects
      Coord a = (*temp_vertices)[v1i];
      Coord b = (*temp_vertices)[v2i];
      Coord c = (*temp_vertices)[v3i];
      Triangle tri;
      tri = Triangle(a, b, c, *transMatrix);              
      if (temp_normals->size() != 0) { //has normals
        Vector vna = (*temp_normals)[vn1i];
        Vector vnb = (*temp_normals)[vn2i];
        Vector vnc = (*temp_normals)[vn3i];
        tri = Triangle(a, b, c, vna, vnb, vnc, *transMatrix);
        //cout << "GOT HERE!!!!!!!!!!!!!! " << endl;
      }
      objects->push_back(tri);
      //cout << "pushed triangle " << tri << endl;
    }
  }
}


//implies that obj filename was parsed and passed in, given WITH quotes, in same directory
void objParse(string filename, vector<Triangle> * objects, Matrix * transMatrix){
  vector<Coord> temp_vertices;
  vector<Vector> temp_normals;
  ifstream objFile(filename);
  if (objFile.is_open()) {
    while (objFile.good()) {
      read_line(objFile, objects, &temp_vertices, transMatrix, &temp_normals);
    }
    objFile.close();
  }
  else {
    cout << "NOTE: Can not open .obj file." << endl;
  }
}
