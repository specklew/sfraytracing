#include "Cameras/OrthographicCamera.h"
#include "SFML/Graphics/Texture.hpp"

OrthographicCamera::OrthographicCamera() = default;
OrthographicCamera::OrthographicCamera(const Vector3 &position, const Vector3 &direction) : Camera(position, direction) {}

OrthographicCamera::OrthographicCamera(const Vector3 &position, const Vector3 &direction, Sampler *sampler) : Camera(
        position, direction, sampler) {

}

sf::Texture OrthographicCamera::renderFrame(int imageWidth) {
    int image_height = static_cast<int>(imageWidth / aspectRatio);

    // SFML Setup
    auto *pixels = new sf::Uint8[imageWidth * image_height * 4];

    sf::Texture buffer;
    buffer.create(imageWidth, image_height);
    sf::Sprite sprite(buffer);

    float viewport_height = 4.0;
    float viewport_width = viewport_height * (static_cast<float>(imageWidth) / image_height);

    Vector3 viewport_u = Vector3(viewport_width, 0,0);
    Vector3 viewport_v = Vector3(0, -viewport_height, 0);

    sampler->pixelDeltaU = viewport_u / static_cast<float>(imageWidth);
    sampler->pixelDeltaV = viewport_v / static_cast<float>(image_height);

    sampler->upperLeftViewportCorner = position - viewport_u / 2.0f - viewport_v / 2.0f + Vector3(0, 0, 1.0f);

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

    delete[] pixels;

    return buffer;
}

Ray OrthographicCamera::calculateRay(const Vector3 &point) const {
    return {point, direction};
}

