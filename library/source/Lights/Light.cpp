#include "Lights/Light.h"

Light::Light(Vector3 position, precision intensity) {
    this->position = position;
    this->color = Color(1,1,1);
    this->intensity = intensity;
}
