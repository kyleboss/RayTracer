class MaterialProps {
  public:
    MaterialProps (Coord location, Color specular, Color ambient, Color diffuse) :
    location(location),
    specular(specular),
    ambient(ambient),
    diffuse(diffuse)
    {}
    Coord location;
    Color specular;
    Color ambient;
    Color diffuse;
};