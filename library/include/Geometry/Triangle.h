#ifndef SFRAYTRACING_TRIANGLE_H
#define SFRAYTRACING_TRIANGLE_H

#include "Vector3.h"
#include "Ray.h"
#include "Geometry.h"

class Triangle : public Geometry{
public:
    Triangle();
    Triangle(Vector3 vertex1, Vector3 vertex2, Vector3 vertex3,
             const std::shared_ptr<Material>& material);
    Triangle(Vector3 vertex1, Vector3 vertex2, Vector3 vertex3,
             Vector3 normal1, Vector3 normal2, Vector3 normal3,
             const std::shared_ptr<Material>&);

    Vector3 vertices[3];
    Vector3 normals[3];


    [[nodiscard]] HitInfo hit(const Ray &ray) const override;

    [[nodiscard]] std::string toString() const;
};

#endif //SFRAYTRACING_TRIANGLE_H
