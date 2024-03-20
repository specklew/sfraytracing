#ifndef SFRAYTRACING_SPHERE_H
#define SFRAYTRACING_SPHERE_H

#include "Vector3.h"
#include "Ray.h"
#include "Geometry.h"
#include <string>
#include <vector>
#include <iostream>


class Sphere : Geometry{
public:
    Vector3 center{};
    float radius{1};

    Sphere();
    Sphere(float r);

    Sphere(Vector3 center, float radius);

    [[nodiscard]] HitInfo hit(const Ray &ray) const override;


    void printIntersectionPoints(std::vector<Vector3> &iPoints);

    [[nodiscard]] std::string toString() const;
};



#endif //SFRAYTRACING_SPHERE_H
