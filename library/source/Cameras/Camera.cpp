#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "Sphere.h"
#include "Color.h"
#include "Ray.h"
#include "Cameras/PerspectiveCamera.h"
#include <cmath>
#include "Cameras/Camera.h"
#include "Samplers/UniformDistributionSuperSampler.h"

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

