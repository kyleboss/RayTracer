class Camera {
  public:
    Camera (float locX, float locY, float locZ, float viewAngle, float viewDirX, float viewDirY, float viewDirZ) : 
    viewAngle(viewAngle), 
    location(locX, locY, locZ), 
    viewDirection(viewDirX, viewDirY, viewDirZ)
    {}
    Coord location;
    float viewAngle;
    Coord viewDirection;
};