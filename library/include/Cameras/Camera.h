//
// Created by macie on 21/03/2024.
//

#ifndef SF_RAYTRACING_CAMERA_H
#define SF_RAYTRACING_CAMERA_H


#include "Vector3.h"
#include "SFML/Graphics/Sprite.hpp"
#include "Samplers/Sampler.h"
#include "HitInfo.h"

class Scene; // Forward declaration

class Camera {

public:
    Vector3 position;
    Vector3 direction;
    Vector3 up;

    int imageWidth;
    int imageHeight;

    double aspectRatio;

    double viewportWidth;
    double viewportHeight;

    Sampler* sampler;
    Scene* scene{};

    Camera();
    Camera(const Vector3& position, const Vector3& direction);
    Camera(const Vector3& position, const Vector3& direction, Sampler *sampler, int imageWidth = 1600);

    virtual ~Camera();

    static void SamplePixel(sf::Uint8 *pixelsArray, Sampler *sampler, const int *imageWidth, int i, int j);

    virtual sf::Texture renderFrame();

    [[nodiscard]] virtual Ray calculateRay(const Vector3 &point) const;
    [[nodiscard]] Color rayColor(const Ray& ray, int depth = 20, const HitInfo &lastHit = {}) const;
};


#endif //SF_RAYTRACING_CAMERA_H
