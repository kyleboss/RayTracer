#include "Coord.h"
#include "Ray.h"
#include "Sample.h"

class Camera {
  public:
    Camera (){};
    Coord LL;
    Coord UL;
    Coord UR;
    Coord LR;
    Coord eyeLoc;
    int canvasX;
    int canvasY;
    float d;
    float midX = Coord::midPoint(LL, LR).x;
    float midY = Coord::midPoint(LL, UL).y;
    float midZ = Coord::midPoint(UL, LR).z;
    Camera (Coord eyeLoc, Coord LL, Coord UL, Coord LR, Coord UR, int canvasX, int canvasY) :
    LL(LL),
    UL(UL),
    LR(LR),
    UR(UR),
    canvasX(canvasX),
    canvasY(canvasY),
    eyeLoc(eyeLoc)
    {}
    Ray shootRay(float u, float v);
};

Ray Camera::shootRay(float u, float v) {
  Coord pointOnPlane = ((LL*v+UL*(1-v))*u+(LR*v + UR*(1-v))*(1-u)) - eyeLoc;
  Vector direction = Vector(-pointOnPlane.x, pointOnPlane.y, pointOnPlane.z).normalize();
  return Ray(eyeLoc, direction, 10, 1, INFINITY);
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
