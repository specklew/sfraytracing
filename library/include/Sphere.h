

#ifndef SFRAYTRACING_SPHERE_H
#define SFRAYTRACING_SPHERE_H

#include "Vector.h"
#include "Ray.h"
#include <string>
#include <vector>
#include <iostream>


class Sphere
{
public:
    Sphere();
    Sphere(float r);
    Sphere(Vector v);
    Sphere(Vector v, float r);

    bool Hit(Ray &ray, std::vector<float> *points, std::vector<Vector> *iPoints, float t_min, float t_max);

    void printIntersectionPoints(std::vector<Vector> &iPoints);


    const Vector &getCenter() const;
    float getRadius() const;

    void setCenter(const Vector &center);
    void setRadius(float radius);

    [[nodiscard]] std::string toString() const;


private:
    Vector Center_;
    float Radius_;
};



#endif //SFRAYTRACING_SPHERE_H
