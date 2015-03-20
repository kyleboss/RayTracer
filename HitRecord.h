#ifndef HITRECORD_H
#define HITRECORD_H

#include "Coord.h"
#include "Vector.h"

class HitRecord {
  public:
    bool isHit;
    bool isSphere;
  	float t;
    Coord intersection;
    Vector normal;
    Sphere sphere;
    Triangle triangle;
    int bounces;
    Ray ray;
    HitRecord(float t, Vector normal, Ray ray) : t(t), normal(normal), isHit(1), isSphere(false), ray(ray) {}
    HitRecord(float t, Coord intersection, Vector normal, Sphere sphere, int bounces, Ray ray) :
    t(t), intersection(intersection), normal(normal), isHit(1), sphere(sphere), isSphere(true), bounces(bounces), ray(ray) {}
    HitRecord(float t, Coord intersection, Vector normal, Triangle triangle, int bounces, Ray ray) :
    t(t), intersection(intersection), normal(normal), isHit(1), triangle(triangle), isSphere(false), bounces(bounces), ray(ray)
    {}
    HitRecord(bool isHit) : isHit(0), isSphere(false) {}
};

std::ostream& operator<< (std::ostream &out, HitRecord &rec)
{
    out << "Hit record at t = " << rec.t <<
        "Intersection @ " << rec.intersection <<
        ", normal: " << rec.normal << "\n";
    return out;
}

#endif
