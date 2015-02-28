class VisibleObject {
  public:
    VisibleObject (double locX, double locY, double locZ, double r, double g, double b, double specular, double ambient, double diffusion) :
    location(locX, locY, locZ),
    color (r, g, b),
    specular(specular),
    ambient(ambient),
    diffusion(diffusion)
    {}
    Coord location;
    Color color;
    double specular;
    double ambient;
    double diffusion;
};