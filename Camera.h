#include "Vector.h"

class Camera {
  public:
<<<<<<< Updated upstream
    Camera (Coord location, float viewAngle, Coord viewDirection) : 
    viewAngle(viewAngle), 
    viewDirection(viewDirection),
    location(location)
    {}
    Coord location;
    float viewAngle;
    Coord viewDirection;
};

std::ostream& operator<< (std::ostream &out, Camera &camera)
{
    out << "viewAngle: " << camera.viewAngle << 
        "viewDirection: " << camera.viewDirection << 
        "location: " << camera.location << "\n";
    return out;
}
=======
    Camera (Vector location, Vector viewDirection, Vector up) :
    location(location),
    viewDirection(viewDirection)
    {}
    Vector location;
    Vectore viewDirection;
    Ray shootRay(Sample sample);
};
>>>>>>> Stashed changes
