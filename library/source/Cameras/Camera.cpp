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
    this->viewportHeight = 2.0f;
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

        //return (Color(1 + info.hitNormal.x,1 + info.hitNormal.y,1 + info.hitNormal.z)) * 0.5f;

        Vector3 dir = Vector3::randomInUnitSphere() + info.hitNormal;
        return rayColor(Ray(info.hitPoint, dir, std::numeric_limits<float>::max(), 0.001f), depth - 1) * 0.5f;
    }

    Vector3 unit_direction = ray.direction.normalized();
    float t = 0.5f * (unit_direction.y + 1.0f);
    return Color(1, 1, 1) * (1.0f - t) + Color(0.5, 0.7, 1) * t;
}

sf::Texture Camera::renderFrame(int imageWidth) {

    int image_height = static_cast<int>(imageWidth / aspectRatio);

    // SFML Setup
    auto *pixels = new sf::Uint8[imageWidth * image_height * 4];

    sf::Texture buffer;
    buffer.create(imageWidth, image_height);
    sf::Sprite sprite(buffer);

    viewportWidth = viewportHeight * (static_cast<float>(imageWidth) / image_height);

    Vector3 viewport_u = Vector3(direction.z, 0,-direction.x).normalized() * viewportWidth;
    Vector3 viewport_v = viewport_u.crossProduct(direction).normalized() * viewportHeight;

    sampler->pixelDeltaU = viewport_u / static_cast<float>(imageWidth);
    sampler->pixelDeltaV = viewport_v / static_cast<float>(image_height);

    sampler->upperLeftViewportCorner = position - viewport_u / 2.0f - viewport_v / 2.0f + direction;

    // Scanlines

    for(int j = 0; j < image_height; ++j){
        for(int i = 0; i < imageWidth; ++i){

            Color pixel_color = sampler->samplePixel(i, j).clamp().linearToGamma(2);

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

