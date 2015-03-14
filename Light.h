#ifndef LIGHT_H
#define LIGHT_H

#include "Color.h"
#include "Coord.h"

class Light {
  public:
    static std::vector<Light *> lights;

    Light (Coord location, Color color, int type, float falloff=0) :
    color (color),
    type(type),
    falloff(falloff),
    location(location)
    {
        lights.push_back(this);
    }
    Color color;
    Coord location;
    int type; //type: 0 = ambient 1 = directional 2 = point
    float falloff; //default = 0, 1 or 2 for dir light
};

std::ostream& operator<< (std::ostream &out, Light &light)
{
    out << "Light type " << light.type << " at "
    "location: " << light.location <<
    ", color: " << light.color << " with falloff " <<
    light.falloff << " \n ";
    return out;
}

std::vector<Light *> Light::lights;

#endif
