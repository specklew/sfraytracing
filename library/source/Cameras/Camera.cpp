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

Camera::Camera() : Camera({0,0,0}, {0,0,0}) {}

Camera::Camera(const Vector3 &position, const Vector3 &direction) :
Camera(
        position,
        direction,
        new UniformDistributionSuperSampler(position, direction, 4)) {}

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

Color Camera::samplePixel(int i, int j) {
    std::vector<Ray> scanLines;
    std::vector<Vector3> sampling_points = sampler->CalculateSamplePoints(i, j);
    for(auto point : sampling_points){
        Vector3 rayDirection = calculateRayDirection(point);
        scanLines.emplace_back(position, rayDirection);
    }

    Color pixel_color = sampler->Sample(scanLines);
    return pixel_color;
}

Vector3 Camera::calculateRayDirection(const Vector3 &point) const {
    return point - position;
}

