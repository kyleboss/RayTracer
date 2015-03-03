class VisibleObject {
  public:
    VisibleObject (float locX, float locY, float locZ, float ksr, float ksg, float ksb, float kar, float kag, float kab, float kdr, float kdg, float kdb) :
    location(locX, locY, locZ),
    specular(ksr, ksg, ksb),
    ambient(kar, kag, kab),
    diffusion(kdr, kdg, kdb)
    {}
    Coord location;
    Color specular;
    Color ambient;
    Color diffusion;
};