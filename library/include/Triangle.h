#ifndef SFRAYTRACING_TRIANGLE_H
#define SFRAYTRACING_TRIANGLE_H

#include "Vector.h"
#include "Ray.h"

class Triangle{
public:
    Triangle();
    Triangle(Vector& vertex1, Vector& vertex2, Vector& vertex3);
    Triangle(Vector& vertex1, Vector& vertex2, Vector& vertex3,
             Vector& normal1, Vector& normal2, Vector& normal3);

    Vector vertices[3];
    Vector normals[3];

    bool Hit(const Ray& ray);

    [[nodiscard]] std::string toString() const;
};

#endif //SFRAYTRACING_TRIANGLE_H
