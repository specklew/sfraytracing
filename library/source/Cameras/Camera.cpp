#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "Sphere.h"
#include "Color.h"
#include "Ray.h"
#include <cmath>
#include "Cameras/Camera.h"
#include "Samplers/UniformDistributionSuperSampler.h"
#include "Scene.h"

Camera::Camera() : Camera({0,0,0}, {0,0,0}) {}

Camera::Camera(const Vector3 &position, const Vector3 &direction) :
Camera(
        position,
        direction,
        new UniformDistributionSuperSampler(4)) {}

Camera::Camera(const Vector3 &position, const Vector3 &direction, Sampler *sampler) {
    this->position = position;
    this->direction = direction.normalized();
    up = Vector3(0, 1, 0);
    aspectRatio = 16.0f / 9.0f;
    this->sampler = sampler;
    this->sampler->center = position;
    this->sampler->camera = this;
}

Camera::~Camera() {
    delete sampler;
}

Ray Camera::calculateRay(const Vector3 &point) const {
    return {position, point - position};
}

Color Camera::rayColor(const Ray &ray, int depth) const {

    if(depth <= 0) return {0,0,0};

    if(HitInfo info = scene->hit(ray); info.intersected){
        Vector3 dir = Vector3::randomOnHemisphere(info.hitNormal);
        return rayColor(Ray(info.hitPoint, dir, std::numeric_limits<float>::max(), 0.001f), depth - 1) * 0.5f;
    }

    Vector3 unit_direction = ray.direction.normalized();
    float t = 0.5f * (unit_direction.y + 1.0f);
    return Color(1, 1, 1) * (1.0f - t) + Color(0.5, 0.7, 1) * t;
}

