#include <complex>
#include "../include/Quaternion.h"


Quaternion::Quaternion() = default;

Quaternion::Quaternion(float scalar, const Vector &vector) {
    this->scalar = scalar;
    this->vector = vector;
}

Quaternion::Quaternion(const Quaternion &quaternion) {
    scalar = quaternion.scalar;
    vector = quaternion.vector;
}

Quaternion& Quaternion::operator=(const Quaternion &quaternion) {
    scalar = quaternion.scalar;
    vector = quaternion.vector;
    return *this;
}

Quaternion Quaternion::operator+(const Quaternion &quaternion) const {
    return {scalar + quaternion.scalar, vector + quaternion.vector};
}

Quaternion Quaternion::operator-(const Quaternion &quaternion) const {
    return {scalar - quaternion.scalar, vector - quaternion.vector};
}

Quaternion Quaternion::operator*(const Quaternion &quaternion) const {
    float s = scalar * quaternion.scalar - vector.DotProduct(quaternion.vector);
    Vector v = vector * quaternion.scalar + quaternion.vector * scalar + vector.CrossProduct(quaternion.vector);
    return {s, v};
}

Quaternion Quaternion::operator*(float f) const {
    return {scalar * f, vector * f};
}

Quaternion Quaternion::operator+=(const Quaternion &quaternion) {
    scalar += quaternion.scalar;
    vector += quaternion.vector;
    return *this;
}

Quaternion Quaternion::operator-=(const Quaternion &quaternion) {
    scalar -= quaternion.scalar;
    vector -= quaternion.vector;
    return *this;
}

Quaternion Quaternion::operator*=(const Quaternion &quaternion) {
    *this = *this * quaternion;
    return *this;
}

Quaternion Quaternion::operator*=(float f) {
    *this = *this * f;
    return *this;
}

float Quaternion::Norm() const {
    float s = scalar * scalar;
    float v = vector.x * vector.x + vector.y * vector.y + vector.z * vector.z;
    return std::sqrt(s + v);
}

Quaternion Quaternion::Normalize() {
    float norm = this->Norm();
    if(norm == 0) return *this;
    *this *= 1/norm;
    return *this;
}

Quaternion Quaternion::Normalized() const {
    float norm = this->Norm();
    if(norm == 0) return *this;
    return *this * (1/norm);
}

Quaternion Quaternion::Conjugate() const {
    return {scalar, vector * -1};
}

Quaternion Quaternion::Inverse() const {
    float absoluteValue = this->Norm();

    if(absoluteValue == 0) return *this;

    absoluteValue *= absoluteValue;
    absoluteValue = 1/absoluteValue;

    Quaternion conjugate = this->Conjugate();

    return conjugate * absoluteValue;
}

Quaternion Quaternion::convertToUnitNorm() {
    float angle = scalar;
    vector.Normalize();
    float s = std::cos(angle * 0.5f);
    Vector v = vector * std::sin(angle * 0.5f);
    return {s, v};
}

std::string Quaternion::toString() const {
    return "{" + std::to_string(scalar) + ", " + vector.toString() + "}";
}
