#include <iostream>

#include <cfloat>
#include <cmath>
#include <vector>
#include "Vector3.h"
#include "Sphere.h"
#include "Ray.h"
#include "Plane.h"
#include "Triangle.h"
#include "Matrix4x4.h"
#include "Quaternion.h"
#include "Cameras/PerspectiveCamera.h"
#include "Scene.h"
#include "Samplers/UniformDistributionSuperSampler.h"
#include "Samplers/AdaptiveSuperSampler.h"
#include <SFML/Graphics.hpp>

void assignment1();

int main() {

    int image_width = 1600;

    //Camera setup
    Camera* camera = new PerspectiveCamera(
            Vector3(0, 0, 0),
            Vector3(0, 0, 1),
            new UniformDistributionSuperSampler(1));

    // Scene setup
    Scene scene = Scene(camera);

    Sphere s1 = Sphere({0, 0, 2}, 0.5f);
    Sphere s2 = Sphere({1, 0, 2}, 1.0f);
    Sphere s3 = Sphere({-2, 0, 2}, 1.0f);
    Triangle t1 = Triangle({0, 0, 2}, {1, 0, 2}, {0, 1, 2});

    scene.addObject(&s1);
    scene.addObject(&s2);
    scene.addObject(&s3);
    scene.addObject(&t1);

    sf::Texture rendered_image = scene.renderScene(image_width);

    sf::Sprite sprite(rendered_image);

    sf::RenderWindow window(sf::VideoMode(sprite.getTextureRect().width, sprite.getTextureRect().height), "Ray Tracer");

    while(window.isOpen()){
        sf::Event event{};
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                window.close();
            }
        }
        window.clear();
        window.draw(sprite);
        window.display();
    }

    //assignment1();

    return 0;
}

void assignment1() {
    std::cout << std::endl << "---- Assignments ----" << std::endl << std::endl;

    Vector3 v1 = {0, 3, 0};
    Vector3 v2 = {5, 5, 0};
    std::cout << "angle between vector " << v1.toString() << " and " << v2.toString() << " = " << v1.angle(v2) << std::endl;

    std::cout << std::endl;

    v1 = {4,5,1};
    v2 = {4,1,3};

    Vector3 perpendicular = v1.crossProduct(v2);
    std::cout << "Vector3 perpendicular to: " << std::endl << "v1 = " << v1.toString() << std::endl << "v2 = " << v2.toString() << std::endl;
    std::cout << "Is " << perpendicular.toString() << std::endl;
    std::cout << "Its angles with v1 and v2 are " << v1.angle(perpendicular) << " and " << v2.angle(perpendicular) << std::endl;
    std::cout << "normalized perpendicular vector is " << perpendicular.normalize().toString() << " with length = " << perpendicular.length() << std::endl << std::endl;

    Sphere S1 = {10.0f};
    Ray r1 = {{0,0,-20},{0,0,1}};
    Ray r2 = {{0,0,-20},{0,1,0}};
    Ray r3 = {{0,10,0},{1,0,0}};
    std::vector<Vector3> intersectionPoints1;
    std::vector<Vector3> intersectionPoints2;
    std::vector<Vector3> intersectionPoints3;
    float t_min=-1;
    float t_max=FLT_MAX;

    HitInfo hitInfo1 = S1.hit(r1);
    HitInfo hitInfo2 = S1.hit(r2);
    HitInfo hitInfo3 = S1.hit(r3);


    std::cout << "For a Sphere 'S1' with a:"  << std::endl << " Center in: " + S1.center.toString() << std::endl << " Radius of: " + std::to_string(S1.radius)<< std::endl;
    std::cout << "And a Ray 'R1' with a: "  << std::endl
    << " Starting point in: " + r1.origin.toString()<< std::endl
    << " Direction: " + r1.direction.toString() << std::endl
    << "The intersection points are: " << std:: endl
    << hitInfo1.hitPoint.toString() << std::endl;

    std::cout << std::endl << std::endl << "For the 'S1' Sphere and a Ray 'R2' with a: "  << std::endl
    << " Starting point in: " + r2.origin.toString() << std::endl
    << " Direction: " + r2.direction.toString() << std::endl
    << "The intersection points are: " << std:: endl
    << hitInfo2.hitPoint.toString() << std::endl;

    std::cout << std::endl << std::endl << "For the 'S1' Sphere and a Ray 'R3' with a: "  << std::endl
    << " Starting point in: " + r3.origin.toString() << std::endl
    << " Direction: " + r3.direction.toString() << std::endl
    << "The intersection points are: " << std:: endl
    << hitInfo3.hitPoint.toString() << std::endl;

    Plane P1= {{0,0,0},{0,1,1}};
    HitInfo P1hit = P1.hit(r2);

    std::cout << std::endl << std::endl << "For the Ray 'R2' and a Plane 'P1' with a: "  << std::endl
    << " Point in: " + P1.point.toString() << std::endl
    << " Normal Vector3 of: " + P1.normal.toString() << std::endl
    << "The intersection points are: " << std:: endl << " ";
    if (P1hit.intersected) {
        std::cout << P1hit.hitPoint.toString() << std::endl;
    } else {
        std::cout << "No intersection with plane P1 and R2." << std::endl;
    }

    std::cout << std::endl;

    v1 = Vector3(0, 0, 0);
    v2 = Vector3(1, 0, 0);
    Vector3 v3 = Vector3(0, 1, 0);
    Triangle t1 = Triangle(v1, v2, v3);

    Vector3 p1 = Vector3(-1, 0.5, 0);
    r1 = Ray(p1, Vector3(1, 0, 0), 2);

    std::cout << "For triangle 'T1': " + t1.toString() << std::endl;
    std::cout << "A ray 'R1' " + r1.toString();
    if(t1.hit(r1).intersected){
        std::cout << " passes through the triangle 'T1'" << std::endl;
    } else {
        std::cout << " does not pass through the triangle 'T1'" << std::endl;
    }

    r2 = Ray(Vector3(2, -1, 0), Vector3(0, 1, 0), 3);

    std::cout << "A ray 'R2' " + r2.toString();
    if(t1.hit(r2).intersected){
        std::cout << " passes through the triangle 'T1'" << std::endl;
    } else {
        std::cout << " does not pass through the triangle 'T1'" << std::endl;
    }

    r3 = Ray(Vector3(0, 0, -1), Vector3(0, 0, 1), 2);

    std::cout << "A ray 'R3' " + r3.toString();
    if(t1.hit(r3).intersected){
        std::cout << " passes through the triangle 'T1'" << std::endl;
    } else {
        std::cout << " does not pass through the triangle 'T1'" << std::endl;
    }

    std::cout << std::endl << "---- Additional assignments ----" << std::endl << std::endl;

    v1 = Vector3(1, 0, 0);

    Matrix4x4 matrix = Matrix4x4::getRotateYMatrix(M_PI * 0.5);
    v2 = matrix.transform(v1);

    std::cout << "Vector3 " << v1.toString() << " rotated 90 degrees around the Y axis is " << v2.toString() << std::endl;

    v1 = Vector3(3, 1, 3);
    Vector3 axis = Vector3(1, 0, 1);
    float angle = M_PI * 0.5;

    std::cout << "Vector3 " << v1.toString() << " rotated 90 degrees around the axis " << axis.toString() << " is "
              << v1.rotateAroundAngleAndAxis(angle, axis).toString() << std::endl;

    Quaternion q1 = Quaternion(M_PI / 6, Vector3(1, 0, 0)).convertToUnitNorm();
    Quaternion q1Inv = q1.inverse();

    std::cout << "Unit norm quaternion " << q1.toString() << " inverted is " << q1Inv.toString() << std::endl;

    q1 = {0.233, Vector3(0.060, -0.257, -0.935)};
    Quaternion q2 = {-0.752, Vector3(0.286, 0.374, 0.459)};

    std::cout << "Quaternion " << q1.toString() << std::endl
    << "multiplied by quaternion " << q2.toString() << std::endl
    << "is " << (q1 * q2).toString() << std::endl;

    std::cout << "Quaternion " << q1.toString() << std::endl
    << "subtracted by quaternion " << q2.toString() << std::endl
    << "is " << (q1 - q2).toString() << std::endl;
}
