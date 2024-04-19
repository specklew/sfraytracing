#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "Geometry/Sphere.h"
#include "Color.h"
#include "Ray.h"
#include "Cameras/Camera.h"
#include "Samplers/UniformDistributionSuperSampler.h"
#include "Scene.h"
#include "Materials/Material.h"
#include "ThreadPool.h"

Camera::Camera() : Camera({0,0,0}, {0,0,-1}) {}

Camera::Camera(const Vector3 &position, const Vector3 &direction) :
Camera(
        position,
        direction,
        new UniformDistributionSuperSampler(4)) {}

Camera::Camera(const Vector3 &position, const Vector3 &direction, Sampler *sampler, int imageWidth) {
    this->position = position;
    this->direction = direction.normalized();
    up = Vector3(0, 1, 0);
    aspectRatio = 16.0f / 9.0f;
    this->imageWidth = imageWidth;
    imageHeight = static_cast<int>(imageWidth / aspectRatio);
    this->sampler = sampler;
    this->sampler->camera = this;
    this->viewportHeight = 2.0f;
}

Camera::~Camera() {
    delete sampler;
}

Ray Camera::calculateRay(const Vector3 &point) const {
    return {position, (point - position).normalize()};
}

Color Camera::rayColor(const Ray &ray, int depth, const HitInfo& lastHit) const {

    if(depth <= 0) return scene->hitLights(lastHit);

    if(HitInfo hit = scene->hit(ray); hit.intersected){

        if(MaterialInfo mat = hit.material->scatter(ray, hit); mat.wasScattered){

            return mat.attenuation * rayColor(mat.scatteredRay, depth - 1, hit);
        } else {
            return scene->hitLights(hit) * mat.attenuation;
        }
    }

    return Color::Black;

    Vector3 unit_direction = ray.direction.normalized();
    float t = 0.5f * (unit_direction.y + 1.0f);
    return Color(1, 1, 1) * (1.0f - t) + Color(0.5, 0.7, 1) * t;
}

void Camera::SamplePixel(sf::Uint8 *pixelsArray, Sampler *sampler, const int *imageWidth, int i, int j) {
    Color pixel_color = sampler->samplePixel(i, j).clamp().linearToGamma(2);

    pixelsArray[(j * *imageWidth + i) * 4 + 0] = (pixel_color.r * 255);
    pixelsArray[(j * *imageWidth + i) * 4 + 1] = (pixel_color.g * 255);
    pixelsArray[(j * *imageWidth + i) * 4 + 2] = (pixel_color.b * 255);
    pixelsArray[(j * *imageWidth + i) * 4 + 3] = 255;
}

sf::Texture Camera::renderFrame() {

    // SFML Setup
    auto *pixels = new sf::Uint8[imageWidth * imageHeight * 4];

    sf::Texture buffer;
    buffer.create(imageWidth, imageHeight);
    sf::Sprite sprite(buffer);

    viewportWidth = viewportHeight * (static_cast<float>(imageWidth) / imageHeight);

    Vector3 viewport_u = Vector3(direction.z, 0,-direction.x).normalized() * viewportWidth;
    Vector3 viewport_v = viewport_u.cross(direction).normalized() * viewportHeight;

    sampler->pixelDeltaU = viewport_u / static_cast<float>(imageWidth);
    sampler->pixelDeltaV = viewport_v / static_cast<float>(imageHeight);

    sampler->upperLeftViewportCorner = position - viewport_u / 2.0 - viewport_v / 2.0 + direction;

    {
        ThreadPool pool(std::thread::hardware_concurrency());
        // Scanlines
        for (int j = 0; j < imageHeight; ++j) {

            pool.enqueue([this, pixels, j] {
                for (int i = 0; i < imageWidth; ++i) {
                    SamplePixel(pixels, sampler, &imageWidth, i, j);
                }
            });
        }
    }

    buffer.update(pixels);

    // Cleanup

    delete[] pixels;

    return buffer;
}

