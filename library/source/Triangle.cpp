#include "Triangle.h"

Triangle::Triangle() = default;

Triangle::Triangle(Vector &vertex1, Vector &vertex2, Vector &vertex3) {
    vertices[0] = vertex1;
    vertices[1] = vertex2;
    vertices[2] = vertex3;

    Vector ab = vertex2 - vertex1;
    Vector ac = vertex3 - vertex1;
    Vector normal = ab.CrossProduct(ac).Normalized();

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

bool Triangle::Hit(const Ray &ray) {
    return false;
}
