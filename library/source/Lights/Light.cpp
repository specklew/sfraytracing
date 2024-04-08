#include "Lights/Light.h"

Light::Light(Vector3 position) {
    this->position = position;
    this->color = Color(1,1,1);
    this->intensity = 1.0f;
}
