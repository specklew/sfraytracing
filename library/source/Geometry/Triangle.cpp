#include <cfloat>
#include "Geometry/Triangle.h"

Triangle::Triangle() = default;

Triangle::Triangle(Vector3 vertex1, Vector3 vertex2, Vector3 vertex3,
                   const std::shared_ptr<Material>& material) {
    this->material = material;

    vertices[0] = vertex1;
    vertices[1] = vertex2;
    vertices[2] = vertex3;

    Vector3 ab = vertex2 - vertex1;
    Vector3 ac = vertex3 - vertex1;
    Vector3 normal = ab.crossProduct(ac).normalized();

    normals[0] = normal;
    normals[1] = normal;
    normals[2] = normal;
}

Triangle::Triangle(Vector3 vertex1, Vector3 vertex2, Vector3 vertex3,
                   Vector3 normal1, Vector3 normal2, Vector3 normal3,
                   const std::shared_ptr<Material>&) {
    this->material = material;

    vertices[0] = vertex1;
    vertices[1] = vertex2;
    vertices[2] = vertex3;

    normals[0] = normal1;
    normals[1] = normal2;
    normals[2] = normal3;
}

HitInfo Triangle::hit(const Ray &ray) const {
    Vector3 ab = vertices[1] - vertices[0];
    Vector3 ac = vertices[2] - vertices[0];
    Vector3 ray_cross_ac = ray.direction.crossProduct(ac);
    float det = ab.dotProduct(ray_cross_ac);

    if(det > -FLT_EPSILON && det < FLT_EPSILON) return {};

    float inv_det  = 1.0f / det;
    Vector3 s = ray.origin - vertices[0];
    float u = s.dotProduct(ray_cross_ac) * inv_det;

    if(u < 0 || u > 1) return {};

    Vector3 s_cross_ab = s.crossProduct(ab);
    float v = ray.direction.dotProduct(s_cross_ab) * inv_det;

    if(v < 0 || u + v > 1) return {};

    float t = ac.dotProduct(s_cross_ab) * inv_det;

    if(t > ray.minimalDistance) return {true, ray.origin + ray.direction * t, normals[0], t, material};

    return {};
}

std::string Triangle::toString() const {
    return "{" + vertices[0].toString() + ", " + vertices[1].toString() + ", " + vertices[2].toString() + "}";
}
