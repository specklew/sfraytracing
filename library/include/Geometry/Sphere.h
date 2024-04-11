#ifndef SFRAYTRACING_SPHERE_H
#define SFRAYTRACING_SPHERE_H

#include "Vector3.h"
#include "Ray.h"
#include "Geometry.h"
#include <string>
#include <vector>
#include <iostream>


class Sphere : public Geometry{
public:
    Vector3 center{};
    float radius{1};

    Sphere();
    Sphere(precision r);

    Sphere(Vector3 center, precision radius, const std::shared_ptr<Material>& material);

    [[nodiscard]] HitInfo hit(const Ray &ray) const override;


    [[nodiscard]] std::string toString() const;
};



#endif //SFRAYTRACING_SPHERE_H
