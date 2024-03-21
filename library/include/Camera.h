#ifndef SFRAYTRACING_CAMERA_H
#define SFRAYTRACING_CAMERA_H

#include "Vector3.h"

class Camera{
public:
    Vector3 position;
    Vector3 direction;
    Vector3 up;

    float fov;
    float aspectRatio;
    float nearPlane;
    float farPlane;

    Camera();
    Camera(const Vector3& position, const Vector3& direction);

    void Render(int imageWidth);
};

#endif //SFRAYTRACING_CAMERA_H
