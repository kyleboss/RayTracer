#include "Camera.h"

Ray Camera::shootRay(Sample sample) {
  Coord start = Coord(1, 1, 1);
  return Ray(start, 1, 1, 1, 5, 0.1, 50);
};
