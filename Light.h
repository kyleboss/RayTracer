class Light {
  public:
    Light (double locX, double locY, double locZ, double r, double g, double b) :
    location(locX, locY, locZ),
    color (r, g, b)
    {}
    Coord location;
    Color color;
};