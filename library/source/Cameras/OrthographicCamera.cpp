#include "Cameras/OrthographicCamera.h"
#include "SFML/Graphics/Texture.hpp"

OrthographicCamera::OrthographicCamera() = default;
OrthographicCamera::OrthographicCamera(const Vector3 &position, const Vector3 &direction) : Camera(position, direction) {}

OrthographicCamera::OrthographicCamera(const Vector3 &position, const Vector3 &direction, Sampler *sampler) : Camera(
        position, direction, sampler) {

}

sf::Texture OrthographicCamera::renderFrame(int imageWidth) {
    return Camera::renderFrame(imageWidth);
}

Ray OrthographicCamera::calculateRay(const Vector3 &point) const {
    return {point, direction};
}

