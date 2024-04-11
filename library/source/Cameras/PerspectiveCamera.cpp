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

    precision theta = fov * pi / half360;
    precision h = std::tan(theta * 0.5);
    viewportHeight = 2 * h;

    return Camera::renderFrame(imageWidth);

}