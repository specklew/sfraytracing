#include "Camera.h"

Camera::Camera() {
    position = Vector3(0, 0, 0);
    direction = Vector3(0, 0, 1);
    up = Vector3(0, 1, 0);
    fov = 60;
    aspectRatio = 16.0f / 9.0f;
    nearPlane = 0.1f;
    farPlane = 1000.0f;
}

Camera::Camera(const Vector3 &position, const Vector3 &direction) {
    this->position = position;
    this->direction = direction;
    up = Vector3(0, 1, 0);
    fov = 60;
    aspectRatio = 16.0f / 9.0f;
    nearPlane = 0.1f;
    farPlane = 1000.0f;
}
