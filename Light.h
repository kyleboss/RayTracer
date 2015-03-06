#ifndef LIGHT_H
#define LIGHT_H

#include "Color.h"
#include "Coord.h"

class Light {
  public:
    Light (Coord location, Color color) :
    location(location),
    color (color)
    {}
    Coord location;
    Color color;
};

std::ostream& operator<< (std::ostream &out, Light &light)
{
    out << "Location: " << light.location <<
    "Color: " << light.color << "\n";
    return out;
}

#endif
