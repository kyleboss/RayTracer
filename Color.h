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
    Color operator * (Color c);
    Color operator + (Color c);
    Color scale(float s);
};
std::ostream& operator<< (std::ostream &out, Color &color)
{
    out << "(" << color.r << ", " <<
        color.g << ", " <<
        color.b << ")\n";
    return out;
}

Color Color::operator * (Color c) {
  return Color(r * c.r, g * c.g, b * c.b);
};

Color Color::operator + (Color c) {
  return Color(r + c.r, g + c.g, b + c.b);
};

Color Color::scale(float s) {
  return Color(r*s, g*s, b*s);
};

#endif
