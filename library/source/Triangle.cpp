#include <cmath>
#include "../include/Triangle.h"

Triangle::Triangle() = default;

Triangle::Triangle(Vector &vertex1, Vector &vertex2, Vector &vertex3) {
    vertices[0] = vertex1;
    vertices[1] = vertex2;
    vertices[2] = vertex3;

    Vector ab = vertex2 - vertex1;
    Vector ac = vertex3 - vertex1;
    Vector normal = ab.crossProduct(ac).normalized();

    normals[0] = normal;
    normals[1] = normal;
    normals[2] = normal;
}

Triangle::Triangle(Vector &vertex1, Vector &vertex2, Vector &vertex3,
                   Vector &normal1, Vector &normal2, Vector &normal3) {
    vertices[0] = vertex1;
    vertices[1] = vertex2;
    vertices[2] = vertex3;

    normals[0] = normal1;
    normals[1] = normal2;
    normals[2] = normal3;
}

bool Triangle::hit(const Ray &ray) {

    Vector ab = vertices[1] - vertices[0];
    Vector ac = vertices[2] - vertices[0];
    Vector normal = ab.crossProduct(ac);
    float dot = normal.dotProduct(ray.getDirection());

    if(fabsf(dot) < std::numeric_limits<float>::epsilon()) return false;
    
    float t = normal.dotProduct(vertices[0] - ray.getOrigin()) / dot;

    if(t < 0.0f) return false;

    Vector intersection = ray.getOrigin() + ray.getDirection() * t;

    Vector ai = intersection - vertices[0];
    Vector bi = intersection - vertices[1];
    Vector ci = intersection - vertices[2];

    Vector bc = vertices[2] - vertices[1];

    Vector v1 = ab.crossProduct(ai);
    Vector v2 = ac.crossProduct(bi);
    Vector v3 = bc.crossProduct(ci);

    if(v1.dotProduct(normal) >= 0.0f
    && v2.dotProduct(normal) >= 0.0f
    && v3.dotProduct(normal) >= 0.0f) return true;

    return false;
}

std::string Triangle::toString() const {
    return "{" + vertices[0].toString() + ", " + vertices[1].toString() + ", " + vertices[2].toString() + "}";
}
