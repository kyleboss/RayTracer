#include "Color.h"

class Material {
  public:
    Material(){}
    Material (Color ambient, Color diffuse, Color specular, float exp, Color reflective) :
    ambient(ambient),
    diffuse(diffuse),
    specular(specular),
    exp(exp),
    reflective(reflective)
    {}
    Color ambient;
    Color diffuse;
    Color specular;
    float exp;
    Color reflective;
};

std::ostream& operator<< (std::ostream &out, Material &material)
{
    out << "Ambient: " << material.ambient <<
        " Diffuse: " << material.diffuse << 
        " Specular: " << material.specular << " with exp " << material.exp <<
        " reflective: " << material.reflective << "\n";
    return out;
}
