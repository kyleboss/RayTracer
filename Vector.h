class Vector {
  public:
    double x, y, z;
    Vector(double x, double y, double z) : x(x), y(y), z(z) {}
    Vector normalize();
    Vector cross(Vector v);
    double dot(Vector v);
    double magnitude();
    Vector operator + (Vector v);
    Vector operator - (Vector v);
    Vector operator * (Vector v);
    Vector operator / (Vector v);
    Vector operator * (double c);
    Vector operator / (double c);
};
