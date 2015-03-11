#ifndef COLOR_H
#define COLOR_H

class Color {
  public:
    Color () {}
    Color (float r, float g, float b) :
    r(r),
    g(g),
    b(b)
    {}
    float r;
    float g;
    float b;
};
std::ostream& operator<< (std::ostream &out, Color &color)
{
    out << "(" << color.r << ", " <<
        color.g << ", " <<
        color.b << ")\n";
    return out;
}

#endif
