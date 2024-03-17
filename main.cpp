#include <iostream>
#include "library/include/Vector.h"
#include "library/include/Sphere.h"
#include "library/include/Ray.h"
#include "library/include/Plane.h"
#include <cfloat>

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

    std::cout << std::endl << std::endl << "For the Ray 'R2' and a Plane 'P1' with a: "  << std::endl << " Point in: " + P1.Point.toString() << std::endl << " Normal Vector of: " + P1.Normal.toString() << std::endl << "The intersection points are: " << std:: endl << " ";

    if (P1hit) {
        std::cout << planeIntersection.toString() << std::endl;
    } else {
        std::cout << "No intersection with plane P1 and R2." << std::endl;
    }

    std::cout << std::endl;


    return 0;
}
