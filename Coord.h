class Coord {
  public:
    Coord (float x, float y, float z) : 
    x(x), 
    y(y), 
    z(z) 
    {}
    float x;
    float y;
    float z;
};

std::ostream& operator<< (std::ostream &out, Coord &coord)
{
    out << "(" << coord.x << ", " <<
        coord.y << ", " <<
        coord.z << ")\n";
    return out;
}