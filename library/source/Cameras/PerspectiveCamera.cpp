#include <cmath>
#include <memory>
#include "Cameras/PerspectiveCamera.h"
#include "Ray.h"
#include "Color.h"
#include "Sphere.h"
#include "SFML/Graphics.hpp"

PerspectiveCamera::PerspectiveCamera() : Camera() {
}

PerspectiveCamera::PerspectiveCamera(const Vector3 &position, const Vector3 &direction) : Camera(position, direction) {
}

PerspectiveCamera::PerspectiveCamera(const Vector3 &position, const Vector3 &direction, Sampler *sampler) : Camera(
        position, direction, sampler) {
}

sf::Texture PerspectiveCamera::renderFrame(int imageWidth) {

    int image_height = static_cast<int>(imageWidth / aspectRatio);

    // SFML Setup
    auto *pixels = new sf::Uint8[imageWidth * image_height * 4];

    sf::Texture buffer;
    buffer.create(imageWidth, image_height);
    sf::Sprite sprite(buffer);

    // PerspectiveCamera Setup

    float theta = fov * M_PI / 180.0f;
    float h = std::tan(theta / 2.0f);

    float viewport_height = 2.0 * h;
    float viewport_width = viewport_height * (static_cast<float>(imageWidth) / image_height);

    Vector3 viewport_u = Vector3(direction.z, 0,-direction.x).normalized() * viewport_width;
    Vector3 viewport_v = viewport_u.crossProduct(direction).normalized() * viewport_height;

    sampler->pixelDeltaU = viewport_u / static_cast<float>(imageWidth);
    sampler->pixelDeltaV = viewport_v / static_cast<float>(image_height);

    sampler->upperLeftViewportCorner = position - viewport_u / 2.0f - viewport_v / 2.0f + direction;

    // Scanlines

    for(int j = 0; j < image_height; ++j){
        for(int i = 0; i < imageWidth; ++i){

            Color pixel_color = sampler->samplePixel(i, j);

            pixels[(j * imageWidth + i) * 4 + 0] = pixel_color.r * 255;
            pixels[(j * imageWidth + i) * 4 + 1] = pixel_color.g * 255;
            pixels[(j * imageWidth + i) * 4 + 2] = pixel_color.b * 255;
            pixels[(j * imageWidth + i) * 4 + 3] = 255;
        }
    }

    buffer.update(pixels);

    // Cleanup

    delete[] pixels;

    return buffer;
}