#include <cmath>
#include <memory>
#include "Cameras/PerspectiveCamera.h"
#include "Ray.h"
#include "Color.h"
#include "Geometry/Sphere.h"
#include "SFML/Graphics.hpp"

PerspectiveCamera::PerspectiveCamera() : Camera() {
}

PerspectiveCamera::PerspectiveCamera(const Vector3 &position, const Vector3 &direction) : Camera(position, direction) {
}

PerspectiveCamera::PerspectiveCamera(const Vector3 &position, const Vector3 &direction, Sampler *sampler) : Camera(
        position, direction, sampler) {
}

sf::Texture PerspectiveCamera::renderFrame(int imageWidth) {

    double theta = fov * M_PI / 180.0f;
    double h = std::tan(theta / 2.0f);
    viewportHeight = 2.0 * h;

    return Camera::renderFrame(imageWidth);

}