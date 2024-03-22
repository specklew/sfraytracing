//
// Created by macie on 21/03/2024.
//

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "Sphere.h"
#include "Color.h"
#include "Ray.h"
#include "Cameras/PerspectiveCamera.h"
#include <cmath>
#include "Cameras/Camera.h"
#include "Samplers/UniformDistributionSuperSampler.h"

Camera::Camera() {
    position = Vector3(0, 0, 0);
    direction = Vector3(0, 0, 1);
    up = Vector3(0, 1, 0);
    aspectRatio = 16.0f / 9.0f;
    sampler = new UniformDistributionSuperSampler(position, 4);
}

Camera::Camera(const Vector3 &position, const Vector3 &direction) {
    this->position = position;
    this->direction = direction;
    up = Vector3(0, 1, 0);
    aspectRatio = 16.0f / 9.0f;
    sampler = new UniformDistributionSuperSampler(position, 4);
}

Camera::Camera(const Vector3 &position, const Vector3 &direction, Sampler *sampler) {
    this->position = position;
    this->direction = direction;
    up = Vector3(0, 1, 0);
    aspectRatio = 16.0f / 9.0f;
    this->sampler = sampler;
    this->sampler->center = position;
}

Camera::~Camera() {
    delete sampler;
}

