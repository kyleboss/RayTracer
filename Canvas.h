#include "Sample.h"

class Canvas {
  public:
    Sample currSample;
    float width;
    float height;
    Canvas(float width, float height) :
    width(width),
    height(height),
    currSample(Sample(0, 0))
    {}
    bool getSample(Sample* sample);
};
