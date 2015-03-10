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
    float midX = Coord::midPoint(LL, LR).x;
    float midY = Coord::midPoint(LL, UL).y;
    float midZ = Coord::midPoint(UL, LR).z;
    Camera (Coord eyeLoc, Coord LL, Coord UL, Coord LR, Coord UR) :
    LL(LL),
    UL(UL),
    LR(LR),
    UR(UR),
    eyeLoc(eyeLoc)
    {
      getWUV();
    }
    Ray shootRay(Sample sample);
    void getWUV();
};

void Camera::getWUV() {
  W = Vector(eyeLoc.x - midX, eyeLoc.y - midY, eyeLoc.z - midZ).normalize();
  Vector up = Vector(0, 1, 0);
  U = up.cross(W).normalize();
  V = W.cross(U);
}

Ray Camera::shootRay(Sample sample) {
  float rayX = UL.x + sample.x;
  float rayY = LL.y + sample.y;
  Vector pointOnPlane = (V * rayY) - W - (U * rayX);
  return Ray(eyeLoc, pointOnPlane - eyeLoc, 5, 1, 100);
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
