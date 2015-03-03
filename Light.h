class Light {
  public:
    Light (float locX, float locY, float locZ, float r, float g, float b) :
    location(locX, locY, locZ),
    color (r, g, b)
    {}
    Coord location;
    Color color;
};