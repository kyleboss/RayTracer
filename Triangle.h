class Triangle {
  public:
     Triangle(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3) : 
     point1(x1, y1, z1),
     point2(x2, y2, z2),
     point3(x3, y3, z3)
     {}
    Coord point1;
    Coord point2;
    Coord point3;
};