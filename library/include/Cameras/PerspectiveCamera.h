#ifndef SFRAYTRACING_CAMERA_H
#define SFRAYTRACING_CAMERA_H

#include "Vector3.h"
#include "Cameras/Camera.h"

class PerspectiveCamera : public Camera {
public:

    float fov{110};

    PerspectiveCamera();
    PerspectiveCamera(const Vector3& position, const Vector3& direction);
    PerspectiveCamera(const Vector3& position, const Vector3& direction, Sampler *sampler);

    sf::Texture RenderFrame(int imageWidth) override;
};

#endif //SFRAYTRACING_CAMERA_H
