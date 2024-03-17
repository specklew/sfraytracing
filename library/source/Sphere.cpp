
#include "../include/Sphere.h"
#include "../include/Vector.h"
#include <cmath>


Sphere::Sphere() = default;

Sphere::Sphere(float r){
    Center_= Vector(0,0,0);
    Radius_=r;
}

Sphere::Sphere(Vector v){
    Center_= v;
    Radius_=1.0f;
}

Sphere::Sphere(Vector v, float r){
    Center_= v;
    Radius_=r;
}

bool Sphere::Hit(Ray ray, std::vector<float> *points, std::vector<Vector> *iPoints, float t_min, float t_max) const {
    Vector rayDirection = ray.getDirection();
    rayDirection.Normalize();
    Vector oc = ray.getOrigin() - Center_;
    float a = rayDirection.DotProduct(rayDirection);
    float b = oc.DotProduct(rayDirection);
    float c = oc.DotProduct(oc) - Radius_ * Radius_;
    float discriminant = b * b - a * c;

    bool hit=false;



    if (discriminant >= 0) {



        float t1 = (-b - std::sqrt(discriminant)) / a;
        float t2 = (-b + std::sqrt(discriminant)) / a;



        if (t1 >= 0 && (t1<t_max && t1>t_min)) {

            Vector tempPoint1 = ray.getOrigin() + rayDirection * t1;
            if (iPoints){
                iPoints->push_back(tempPoint1);
            }
            if(points){
                points->push_back(t1);
            }
            hit=true;
        }

        if (t2 >= 0 && t1 != t2 && (t2<t_max && t2>t_min)) {
            Vector tempPoint2 = ray.getOrigin() + rayDirection * t2;

            if (iPoints){
                iPoints->push_back(tempPoint2);
            }
            if(points){
                points->push_back(t2);

            }
            hit=true;
        }

    }
    return hit;
}





const Vector &Sphere::getCenter() const {
    return Center_;
}
float Sphere::getRadius() const {
    return Radius_;
}



void Sphere::setCenter(const Vector &center) {
    Center_ = center;
}
void Sphere::setRadius(float radius) {
    Radius_ = radius;
}

std::string Sphere::toString() const {
    return "Center: " + this->getCenter().toString() + ", Radius: " + std::to_string(this->getRadius());
}

void Sphere::printIntersectionPoints(std::vector<Vector> &iPoints) {
    if (!iPoints.empty()){
        for (Vector v : iPoints) {
            std::cout << v.toString() << "   ";
        }
    }
    else{
        std::cout << "No intersections." << std::endl;
    }
}



