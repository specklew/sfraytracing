#ifndef SF_RAYTRACING_ORTHOGRAPHICCAMERA_H
#define SF_RAYTRACING_ORTHOGRAPHICCAMERA_H

#include "Camera.h"

class OrthographicCamera : Camera {
public:
    OrthographicCamera();
    OrthographicCamera(const Vector3& position, const Vector3& direction);
    OrthographicCamera(const Vector3& position, const Vector3& direction, Sampler *sampler);

    sf::Texture renderFrame(int imageWidth) override;
};

#endif //SF_RAYTRACING_ORTHOGRAPHICCAMERA_H
