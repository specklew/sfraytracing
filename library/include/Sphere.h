

#ifndef SFRAYTRACING_SPHERE_H
#define SFRAYTRACING_SPHERE_H

#include "Vector3.h"
#include "Ray.h"
#include <string>
#include <vector>
#include <iostream>


class Sphere
{
public:
    Sphere();
    Sphere(float r);
    Sphere(Vector3 center);
    Sphere(Vector3 center, float radius);

    bool hit(Ray &ray, std::vector<float> *t_points, std::vector<Vector3> *iPoints, float t_min, float t_max);

    void printIntersectionPoints(std::vector<Vector3> &iPoints);


    [[nodiscard]] const Vector3 &getCenter() const;
    [[nodiscard]] float getRadius() const;

    void setCenter(const Vector3 &center);
    void setRadius(float radius);

    [[nodiscard]] std::string toString() const;


private:
    Vector3 Center_;
    float Radius_;
};



#endif //SFRAYTRACING_SPHERE_H
