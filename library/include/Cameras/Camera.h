//
// Created by macie on 21/03/2024.
//

#ifndef SF_RAYTRACING_CAMERA_H
#define SF_RAYTRACING_CAMERA_H


#include "Vector3.h"
#include "SFML/Graphics/Sprite.hpp"
#include "Samplers/Sampler.h"

class Scene; // Forward declaration

class Camera {

public:
    Vector3 position;
    Vector3 direction;
    Vector3 up;

    float aspectRatio;

    float viewportWidth;
    float viewportHeight;

    Sampler* sampler;
    Scene* scene{};

    Camera();
    Camera(const Vector3& position, const Vector3& direction);
    Camera(const Vector3& position, const Vector3& direction, Sampler *sampler);

    virtual ~Camera();

    virtual sf::Texture renderFrame(int imageWidth);

    [[nodiscard]] virtual Ray calculateRay(const Vector3 &point) const;
    [[nodiscard]] Color rayColor(const Ray& ray, int depth = 1) const;
};


#endif //SF_RAYTRACING_CAMERA_H
