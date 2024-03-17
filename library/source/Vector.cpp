#include <cmath>
#include "../include/Vector.h"

Vector::Vector() = default;

Vector::Vector(float x, float y, float z) {
    x = x;
    y = y;
    z = z;
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

Vector Vector::operator*=(const float &scalar) {
    x *= scalar;
    y *= scalar;
    z *= scalar;
    return *this;
}

Vector Vector::operator/=(const float &scalar) {
    x /= scalar;
    y /= scalar;
    z /= scalar;
    return *this;
}

//Other methods

float Vector::DotProduct(const Vector &other) const{
    return x * other.x + y * other.y + z * other.z;
}

Vector Vector::CrossProduct(const Vector &other) const {
    return {y * other.z - z * other.y,
            z * other.x - x * other.z,
            x * other.y - y * other.x};
}

Vector Vector::Normalize() {
    float length = this->Length();
    if(length == 0) return *this;
    *this/=length;
    return *this;
}

Vector Vector::Normalized() const {
    float length = this->Length();
    if(length == 0) return *this;
    return *this/length;
}

float Vector::Length() const {
    return std::sqrt(x * x + y * y + z * z);
}

float Vector::Angle(Vector other) const {
    float dot = this->DotProduct(other);
    float lenSq1 = x * x + y * y + z * z;
    float lenSq2 = other.x * other.x + other.y * other.y + other.z * other.z;
    float angle = std::acos(dot/ std::sqrt(lenSq1 * lenSq2));
    return angle;
}

std::string Vector::toString() const {
    return "[" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + "]";
}
