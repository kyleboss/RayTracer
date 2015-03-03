class VisibleObject {
  public:
    VisibleObject (double locX, double locY, double locZ, double ksr, double ksg, double ksb, double kar, double kag, double kab, double kdr, double kdg, double kdb) :
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