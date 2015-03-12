#include "Sample.h"

class Canvas {
  public:
    Sample currSample;
    float width;
    float height;
    Canvas(float width, float height) :
    width(width),
    height(height),
    currSample(Sample(-1, 0))
    {}
    bool getSample(Sample* sample);
};
bool Canvas::getSample(Sample* sample) {
  if (sample->x == (width - 1) && sample->y == (height - 1)) {
    return false;
  }
  if (sample->x == (width - 1)) {
    currSample.x = 0;
    currSample.y++;
    return true;
  }
  currSample.x++;
  return true;
}
