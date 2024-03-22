#include "Cameras/OrthographicCamera.h"

OrthographicCamera::OrthographicCamera() = default;
OrthographicCamera::OrthographicCamera(const Vector3 &position, const Vector3 &direction) : Camera(position, direction) {}

OrthographicCamera::OrthographicCamera(const Vector3 &position, const Vector3 &direction, Sampler *sampler) : Camera(
        position, direction, sampler) {

}

