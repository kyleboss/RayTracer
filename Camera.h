#include "Coord.h"
#include "Ray.h"
#include "Sample.h"

class Camera {
  public:
    Coord LL;
    Coord UL;
    Coord UR;
    Coord LR;
    Coord eyeLoc;
    Vector W;
    Vector U;
    Vector V;
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
    {
      getWUV();
    }
    Ray shootRay(Sample sample);
    void getWUV();
};

void Camera::getWUV() {
  W = Vector(eyeLoc.x - midX, eyeLoc.y - midY, eyeLoc.z - midZ);
  d = W.magnitude();
  W.normalize();
  Vector up = Vector(0, 1, 0);
  U = up.cross(W).normalize();
  V = W.cross(U);
}

Ray Camera::shootRay(Sample sample) {
  float rayu = UL.x + (UR.x - UL.x) * (sample.x + 0.5) / canvasX;
  float rayv = LR.y + (UR.y - LR.y) * (sample.y + 0.5) / canvasY;

  Vector direction = W * -d + U * rayu + V * rayv;
  //Vector pointOnPlane = (V * rayY) - W - (U * rayX);
  return Ray(eyeLoc, direction, 5, 1, 100);
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
