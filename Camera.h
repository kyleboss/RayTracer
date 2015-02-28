class Camera {
  public:
    Camera (double locX, double locY, double locZ, double viewAngle, double viewDirX, double viewDirY, double viewDirZ) : 
    viewAngle(viewAngle), 
    location(locX, locY, locZ), 
    viewDirection(viewDirX, viewDirY, viewDirZ)
    {}
    Coord location;
    double viewAngle;
    Coord viewDirection;
};