#include "Coord.h"
#include "Ray.h"
#include "Sample.h"

class Camera {
  public:
    Camera (Coord location, float viewAngle, Coord viewDirection) :
    viewAngle(viewAngle),
    viewDirection(viewDirection),
    location(location)
    {}
    Coord location;
    float viewAngle;
    Coord viewDirection;
    Ray shootRay(Sample sample);
};

std::ostream& operator<< (std::ostream &out, Camera &camera)
{
    out << "viewAngle: " << camera.viewAngle <<
        "viewDirection: " << camera.viewDirection <<
        "location: " << camera.location << "\n";
    return out;
}
