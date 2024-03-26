#include <cmath>
#include "Triangle.h"

Triangle::Triangle() = default;

Triangle::Triangle(Vector3 vertex1, Vector3 vertex2, Vector3 vertex3) {
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
                   Vector3 normal1, Vector3 normal2, Vector3 normal3) {
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
    Vector3 normal = ab.crossProduct(ac);
    float dot = normal.dotProduct(ray.direction);

    if(fabsf(dot) < std::numeric_limits<float>::epsilon()) return {};

    float t = normal.dotProduct(vertices[0] - ray.origin) / dot;

    if(t < 0.0f) return {};

    Vector3 intersection = ray.origin + ray.direction * t;

    Vector3 ai = intersection - vertices[0];
    Vector3 bi = intersection - vertices[1];
    Vector3 ci = intersection - vertices[2];

    Vector3 bc = vertices[2] - vertices[1];

    Vector3 v1 = ab.crossProduct(ai);
    Vector3 v2 = ac.crossProduct(bi);
    Vector3 v3 = bc.crossProduct(ci);

    if(v1.dotProduct(normal) >= 0.0f
       && v2.dotProduct(normal) >= 0.0f
       && v3.dotProduct(normal) >= 0.0f) return {true, intersection, normal};

    return {};
}

std::string Triangle::toString() const {
    return "{" + vertices[0].toString() + ", " + vertices[1].toString() + ", " + vertices[2].toString() + "}";
}
