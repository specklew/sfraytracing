//
// Created by macie on 21/03/2024.
//

#ifndef SF_RAYTRACING_CAMERA_H
#define SF_RAYTRACING_CAMERA_H


#include "Vector3.h"
#include "SFML/Graphics/Sprite.hpp"
#include "Samplers/Sampler.h"

class Camera {

public:
    Vector3 position;
    Vector3 direction;
    Vector3 up;

    float aspectRatio;

    Sampler* sampler;

    Camera();
    Camera(const Vector3& position, const Vector3& direction);
    Camera(const Vector3& position, const Vector3& direction, Sampler *sampler);

    virtual ~Camera();

    virtual sf::Texture RenderFrame(int imageWidth) = 0;
};


#endif //SF_RAYTRACING_CAMERA_H
