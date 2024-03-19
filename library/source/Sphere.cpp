
#include "../include/Sphere.h"
#include "../include/Vector3.h"
#include <cmath>


Sphere::Sphere() = default;

Sphere::Sphere(float r){
    Center_ = Vector3(0, 0, 0);
    Radius_ = r;
}

Sphere::Sphere(Vector3 center){
    Center_ = center;
    Radius_ = 1.0f;
}

Sphere::Sphere(Vector3 center, float radius){
    Center_ = center;
    Radius_ = radius;
}

bool Sphere::hit(Ray &ray, std::vector<float> *t_points, std::vector<Vector3> *iPoints, float t_min, float t_max) {
    Vector3 rayDirection = ray.getDirection();
    rayDirection.normalize();

    Vector3 oc = ray.getOrigin() - Center_;
    float a = rayDirection.dotProduct(rayDirection);
    float b = oc.dotProduct(rayDirection);
    float c = oc.dotProduct(oc) - Radius_ * Radius_;
    float discriminant = b * b -  a * c;

    bool hit = false;


    if (discriminant >= 0) {


        float t1 = (-b - std::sqrt(discriminant)) /  a;
        float t2 = (-b + std::sqrt(discriminant)) /  a;

        if (t1 >= 0 && (t1<t_max && t1>t_min)) {

            Vector3 tempPoint1 = ray.getOrigin() + rayDirection * t1;
            if (iPoints){
                iPoints->push_back(tempPoint1);
            }
            if(t_points){
                t_points->push_back(t1);
            }
            hit=true;
        }

        if (t2 >= 0 && t1 != t2 && (t2<t_max && t2>t_min)) {
            Vector3 tempPoint2 = ray.getOrigin() + rayDirection * t2;

            if (iPoints){
                iPoints->push_back(tempPoint2);
            }
            if(t_points){
                t_points->push_back(t2);

            }
            hit=true;
        }

    }
    return hit;
}





const Vector3 &Sphere::getCenter() const {
    return Center_;
}
float Sphere::getRadius() const {
    return Radius_;
}



void Sphere::setCenter(const Vector3 &center) {
    Center_ = center;
}
void Sphere::setRadius(float radius) {
    Radius_ = radius;
}

std::string Sphere::toString() const {
    return "Center: " + this->getCenter().toString() + ", Radius: " + std::to_string(this->getRadius());
}

void Sphere::printIntersectionPoints(std::vector<Vector3> &iPoints) {
    if (!iPoints.empty()){
        for (Vector3 v : iPoints) {
            std::cout << v.toString() << "   ";
        }
    }
    else{
        std::cout << "No intersections." << std::endl;
    }
}



