#include <cmath>
#include "../include/Vector.h"
#include "../include/Quaternion.h"

Vector::Vector() = default;

Vector::Vector(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

Vector::Vector(const Vector& p1, const Vector& p2) {
    x = p2.x - p1.x;
    y = p2.y - p1.y;
    z = p2.z - p1.z;
}

//Operators overloads

Vector Vector::operator+(const Vector &other) const {
    return {x + other.x, y + other.y, z + other.z};
}

Vector Vector::operator-(const Vector &other) const {
    return {x - other.x, y - other.y, z - other.z};
}

Vector Vector::operator*(const float &scalar) const {
    return {x * scalar, y * scalar, z * scalar};
}

Vector Vector::operator/(const float &scalar) const {
    return {x / scalar, y / scalar, z / scalar};
}

//Equals operators overloads

Vector Vector::operator+=(const Vector &other) {
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
}

Vector Vector::operator-=(const Vector &other) {
    x -= other.x;
    y -= other.y;
    z -= other.z;
    return *this;
}

Vector Vector::operator*=(float scalar) {
    x *= scalar;
    y *= scalar;
    z *= scalar;
    return *this;
}

Vector Vector::operator/=(float scalar) {
    x /= scalar;
    y /= scalar;
    z /= scalar;
    return *this;
}

//Other methods

float Vector::dotProduct(const Vector &other) const{
    return x * other.x + y * other.y + z * other.z;
}

Vector Vector::crossProduct(const Vector &other) const {
    return {y * other.z - z * other.y,
            z * other.x - x * other.z,
            x * other.y - y * other.x};
}

Vector Vector::normalize() {
    float length = this->length();
    if(length == 0) return *this;
    *this/=length;
    return *this;
}

Vector Vector::normalized() const {
    float length = this->length();
    if(length == 0) return *this;
    return *this/length;
}

float Vector::length() const {
    return std::sqrt(x * x + y * y + z * z);
}

float Vector::angle(Vector other) const {
    float dot = this->dotProduct(other);
    float lenSq1 = x * x + y * y + z * z;
    float lenSq2 = other.x * other.x + other.y * other.y + other.z * other.z;
    float angle = std::acos(dot/ std::sqrt(lenSq1 * lenSq2));
    return angle;
}

std::string Vector::toString() const {
    return "[" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + "]";
}

Vector Vector::rotateAroundAngleAndAxis(float angle, Vector &axis) const {
    Quaternion pure = {0, *this};
    axis.normalize();

    Quaternion q = {angle, axis};
    q = q.convertToUnitNorm();
    Quaternion qInv = q.inverse();
    Quaternion rotatedVector = q * pure * qInv;

    return rotatedVector.vector;
}
