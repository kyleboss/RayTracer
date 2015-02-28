#include <math.h>
#include <iostream>
#include "Color.h"
#include "Canvas.h"
#include "Coord.h"
#include "Camera.h"
#include "Light.h"
#include "VisibleObject.h"


using namespace std;

int main (int argc, char *argv[]) {
  Canvas canvas = Canvas(400.0, 40.0);
  Camera cam = Camera(1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0);
  Light light = Light (1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
  VisibleObject visObj = VisibleObject(1, 2, 3, 4, 5, 6, 7, 8, 9);
  cout << light.color.r;
  cout << "rendering..." << endl;
  return 0;
}