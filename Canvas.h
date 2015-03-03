#include "Sample.h"

class Canvas {
  public:
    Sample currSample;
    double width;
    double height;
    Canvas(double width, double height) :
    width(width),
    height(height),
    currSample(Sample(0, 0))
    {}
    bool getSample(Sample* sample);
};
