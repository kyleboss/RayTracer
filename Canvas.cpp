#include "Canvas.h"

bool Canvas::getSample(Sample* sample) {
  if (sample.x == (width - 1) && sample.y == (height - 1)) {
    return false;
  }
  if (sample.x == (width - 1)) {
    currSample.x = 0;
    currSample.y++;
    return true;
  }
  currSample.x++;
  return true;
}
