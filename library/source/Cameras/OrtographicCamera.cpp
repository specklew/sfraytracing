#include "Cameras/OrtographicCamera.h"

OrtographicCamera::OrtographicCamera() = default;
OrtographicCamera::OrtographicCamera(const Vector3 &position, const Vector3 &direction) : Camera(position, direction) {}

OrtographicCamera::OrtographicCamera(const Vector3 &position, const Vector3 &direction, Sampler *sampler) : Camera(
        position, direction, sampler) {

}

