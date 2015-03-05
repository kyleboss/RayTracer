class Triangle {
  public:
     Triangle(Coord point1, Coord point2, Coord point3) : 
     point1(point1),
     point2(point2),
     point3(point3)
     {}
     Triangle(Coord p1, Coord p2, Coord p3) :
     point1 = p1,
	 point2 = p2,
	 point3 = p3
	 {}
    Coord point1;
    Coord point2;
    Coord point3;
};

std::ostream& operator<< (std::ostream &out, Triangle &triangle)
{
    out << "Triangle: (" << triangle.point1 << ", " <<
        triangle.point2 << ", " <<
        triangle.point3 << ")\n";
    return out;
}
