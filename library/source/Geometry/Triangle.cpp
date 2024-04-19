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
    Vector3 normal = ab.cross(ac).normalized();

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
    Vector3 ray_cross_ac = ray.direction.cross(ac);
    precision det = ab.dot(ray_cross_ac);

    if(det > -epsilon && det < epsilon) return {};

    precision inv_det  = 1.0f / det;
    Vector3 s = ray.origin - vertices[0];
    precision u = s.dot(ray_cross_ac) * inv_det;

    if(u < 0 || u > 1) return {};

    Vector3 s_cross_ab = s.cross(ab);
    precision v = ray.direction.dot(s_cross_ab) * inv_det;

    if(v < 0 || u + v > 1) return {};

    precision t = ac.dot(s_cross_ab) * inv_det;

    bool front_face;
    Vector3 normal = normals[0].normalized();
    if(ray.direction.dot(normal) > 0){
        front_face = false;
        normal = -normal;
    } else {
        front_face = true;
    }


    if(t > ray.minimalDistance) {
        return {true, front_face, ray.origin + ray.direction * t,
                normal, t, material, ray
        };
    }

    return {};
}

std::string Triangle::toString() const {
    return "{" + vertices[0].toString() + ", " + vertices[1].toString() + ", " + vertices[2].toString() + "}";
}
