#include <complex>
#include "Quaternion.h"


Quaternion::Quaternion() = default;

Quaternion::Quaternion(precision scalar, const Vector3 &vector) {
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
    double s = scalar * quaternion.scalar - vector.dot(quaternion.vector);
    Vector3 v = vector * quaternion.scalar + quaternion.vector * scalar + vector.cross(quaternion.vector);
    return {s, v};
}

Quaternion Quaternion::operator*(precision f) const {
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

Quaternion Quaternion::operator*=(precision f) {
    this->vector *= f;
    this->scalar *= f;
    return *this;
}

precision Quaternion::norm() const {
    precision s = scalar * scalar;
    precision v = vector.x * vector.x + vector.y * vector.y + vector.z * vector.z;
    return std::sqrt(s + v);
}

Quaternion Quaternion::normalize() {
    precision norm = this->norm();
    if(norm == 0) return *this;
    *this *= 1/norm;
    return *this;
}

Quaternion Quaternion::normalized() const {
    precision norm = this->norm();
    if(norm == 0) return *this;
    return *this * (1/norm);
}

Quaternion Quaternion::conjugate() const {
    return {scalar, vector * -1};
}

Quaternion Quaternion::inverse() const {
    precision absoluteValue = this->norm();

    if(absoluteValue == 0) return *this;

    absoluteValue *= absoluteValue;
    absoluteValue = 1/absoluteValue;

    Quaternion conjugate = this->conjugate();

    return conjugate * absoluteValue;
}

Quaternion Quaternion::convertToUnitNorm() {
    precision angle = scalar;
    vector.normalize();
    precision s = std::cos(angle * 0.5);
    Vector3 v = vector * std::sin(angle * 0.5);
    return {s, v};
}

std::string Quaternion::toString() const {
    return "{" + std::to_string(scalar) + ", " + vector.toString() + "}";
}
