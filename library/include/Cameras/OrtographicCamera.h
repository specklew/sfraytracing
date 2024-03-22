#ifndef SF_RAYTRACING_ORTOGRAPHICCAMERA_H
#define SF_RAYTRACING_ORTOGRAPHICCAMERA_H

#include "Camera.h"

class OrtographicCamera : Camera {
public:
    OrtographicCamera();
    OrtographicCamera(const Vector3& position, const Vector3& direction);
    OrtographicCamera(const Vector3& position, const Vector3& direction, Sampler *sampler);

    sf::Texture RenderFrame(int imageWidth) override;
};

#endif //SF_RAYTRACING_ORTOGRAPHICCAMERA_H
