#include "Coord.h"
#include "Ray.h"
#include "Sample.h"

class Camera {
  public:
    Camera (Coord eyeLoc, Coord LL, Coord UL, Coord LR, Coord UR) :
    LL(LL),
    UL(UL),
    LR(LR),
    UR(UR),
    eyeLoc(eyeLoc)
    {}
    Coord LL;
    Coord UL;
    Coord UR;
    Coord LR;
    Coord eyeLoc;
    float midX = Coord::midPoint(LL, LR).x;
    float midY = Coord::midPoint(LL, UL).y;
    Ray shootRay(Sample sample);
};

Ray Camera::shootRay(Sample sample) {
  Coord coord = Coord(1, 1, 1);
  Ray ray = Ray(coord, 1.0, 1.0, 1.0, 1, 1.0, 1.0);
  return ray;
}

std::ostream& operator<< (std::ostream &out, Camera &camera)
{
    out << "eyeLoc: " << camera.eyeLoc <<
        "LL: " << camera.LL <<
        "UL: " << camera.UL <<
        "UR: " << camera.UR <<
        "LR: " << camera.LR << "\n";
    return out;
}
