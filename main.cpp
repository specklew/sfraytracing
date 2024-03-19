#include <iostream>

#include <cfloat>
#include <cmath>
#include "library/include/Vector.h"
#include "library/include/Ray.h"
#include "library/include/Sphere.h"
#include "library/include/Plane.h"
#include "library/include/Triangle.h"
#include "library/include/Matrix4x4.h"
#include "library/include/Quaternion.h"

int main() {

    std::cout << std::endl << "---- Assignments ----" << std::endl << std::endl;

    Vector v1 = {0, 3, 0};
    Vector v2 = {5, 5, 0};
    std::cout << "Angle between vector " << v1.toString() << " and " << v2.toString() << " = " << v1.Angle(v2) << std::endl;

    std::cout << std::endl;

    v1 = {4,5,1};
    v2 = {4,1,3};

    Vector perpendicular = v1.CrossProduct(v2);
    std::cout << "Vector perpendicular to: " << std::endl << "v1 = " << v1.toString() << std::endl << "v2 = " << v2.toString() << std::endl;
    std::cout << "Is " << perpendicular.toString() << std::endl;
    std::cout << "Its angles with v1 and v2 are " << v1.Angle(perpendicular) << " and " << v2.Angle(perpendicular) << std::endl;
    std::cout << "Normalized perpendicular vector is " << perpendicular.Normalize().toString() << " with length = " << perpendicular.Length() << std::endl << std::endl;

    Sphere S1 = {10.0f};
    Ray r1={{0,0,-20},{0,0,1}};
    Ray r2={{0,0,-20},{0,1,0}};
    Ray r3={{0,10,0},{1,0,0}};
    std::vector<Vector> intersectionPoints1;
    std::vector<Vector> intersectionPoints2;
    std::vector<Vector> intersectionPoints3;
    float t_min=-1;
    float t_max=FLT_MAX;

    S1.Hit(r1, nullptr, &intersectionPoints1, t_min, t_max);
    S1.Hit(r2, nullptr, &intersectionPoints2, t_min, t_max);
    S1.Hit(r3, nullptr, &intersectionPoints3, t_min, t_max);


    std::cout << "For a Sphere 'S1' with a:"  << std::endl << " Center in: " + S1.getCenter().toString() << std::endl << " Radius of: " + std::to_string(S1.getRadius())<< std::endl;
    std::cout << "And a Ray 'R1' with a: "  << std::endl << " Starting point in: " + r1.getOrigin().toString() << std::endl << " Direction: " + r1.getDirection().toString() << std::endl << "The intersection points are: " << std:: endl << " ";
    S1.printIntersectionPoints(intersectionPoints1);

    std::cout << std::endl << std::endl << "For the 'S1' Sphere and a Ray 'R2' with a: "  << std::endl << " Starting point in: " + r2.getOrigin().toString() << std::endl << " Direction: " + r2.getDirection().toString() << std::endl << "The intersection points are: " << std:: endl << " ";
    S1.printIntersectionPoints(intersectionPoints2);

    std::cout << std::endl << std::endl << "For the 'S1' Sphere and a Ray 'R3' with a: "  << std::endl << " Starting point in: " + r3.getOrigin().toString() << std::endl << " Direction: " + r3.getDirection().toString() << std::endl << "The intersection points are: " << std:: endl << " ";
    S1.printIntersectionPoints(intersectionPoints3);

    Plane P1= {{0,0,0},{0,1,1}};
    Vector planeIntersection;
    bool P1hit = P1.Intersect(r2,planeIntersection);

    std::cout << std::endl << std::endl << "For the Ray 'R2' and a Plane 'P1' with a: "  << std::endl << " Point in: " + P1.getPoint().toString() << std::endl << " Normal Vector of: " + P1.getNormal().toString() << std::endl << "The intersection points are: " << std:: endl << " ";
    if (P1hit) {
        std::cout << planeIntersection.toString() << std::endl;
    } else {
        std::cout << "No intersection with plane P1 and R2." << std::endl;
    }

    std::cout << std::endl;

    v1 = Vector(0,0,0);
    v2 = Vector(1,0,0);
    Vector v3 = Vector(0,1,0);
    Triangle t1 = Triangle(v1, v2, v3);

    Vector p1 = Vector(-1, 0.5, 0);
    r1 = Ray(p1, Vector(1, 0, 0), 2);

    std::cout << "For triangle 'T1': " + t1.toString() << std::endl;
    std::cout << "A ray 'R1' " + r1.toString();
    if(t1.Hit(r1)){
        std::cout << " passes through the triangle 'T1'" << std::endl;
    } else {
        std::cout << " does not pass through the triangle 'T1'" << std::endl;
    }

    r2 = Ray(Vector(2,-1,0), Vector(0,1,0), 3);

    std::cout << "A ray 'R2' " + r2.toString();
    if(t1.Hit(r2)){
        std::cout << " passes through the triangle 'T1'" << std::endl;
    } else {
        std::cout << " does not pass through the triangle 'T1'" << std::endl;
    }

    r3 = Ray(Vector(0,0,-1), Vector(0,0,1), 2);

    std::cout << "A ray 'R3' " + r3.toString();
    if(t1.Hit(r3)){
        std::cout << " passes through the triangle 'T1'" << std::endl;
    } else {
        std::cout << " does not pass through the triangle 'T1'" << std::endl;
    }

    std::cout << std::endl << "---- Additional assignments ----" << std::endl << std::endl;

    v1 = Vector(1,0,0);

    Matrix4x4 matrix = Matrix4x4::getRotateYMatrix(M_PI * 0.5);
    v2 = matrix.Transform(v1);

    std::cout << "Vector " << v1.toString() << " rotated 90 degrees around the Y axis is " << v2.toString() << std::endl;

    v1 = Vector(3,1,3);
    Vector axis = Vector(1,0,1);
    float angle = M_PI * 0.5;

    std::cout << "Vector " << v1.toString() << " rotated 90 degrees around the axis " << axis.toString() << " is "
    << v1.RotateAroundAngleAndAxis(angle, axis).toString() << std::endl;

    Quaternion q1 = Quaternion(M_PI / 6, Vector(1,0,0)).convertToUnitNorm();
    Quaternion q1Inv = q1.Inverse();

    std::cout << "Unit norm quaternion " << q1.toString() << " inverted is " << q1Inv.toString() << std::endl;

    q1 = {0.233, Vector(0.060, -0.257, -0.935)};
    Quaternion q2 = {-0.752, Vector(0.286, 0.374, 0.459)};

    std::cout << "Quaternion " << q1.toString() << std::endl
    << "multiplied by quaternion " << q2.toString() << std::endl
    << "is " << (q1 * q2).toString() << std::endl;

    std::cout << "Quaternion " << q1.toString() << std::endl
    << "subtracted by quaternion " << q2.toString() << std::endl
    << "is " << (q1 - q2).toString() << std::endl;
    return 0;
}
