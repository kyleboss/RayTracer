class Camera {
  public:
    Camera (Coord location, float viewAngle, Coord viewDirection) : 
    viewAngle(viewAngle), 
    viewDirection(viewDirection),
    location(location)
    {}
    Coord location;
    float viewAngle;
    Coord viewDirection;
};