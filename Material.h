class Material {
  public:
    Material (Coord location, Color specular, Color ambient, Color diffuse) :
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

std::ostream& operator<< (std::ostream &out, Material &material)
{
    out << "Location: " << material.location << 
        "Specular: " << material.specular << 
        "Ambient: " << material.ambient << 
        "Diffuse: " << material.diffuse << "\n";
    return out;
}