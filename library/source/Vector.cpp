#include <cmath>
#include "../include/Vector.h"

Vector::Vector() = default;

Vector::Vector(float x, float y, float z) {
    X = x;
    Y = y;
    Z = z;
}

Vector::Vector(const Vector& p1, const Vector& p2) {
    X = p2.X - p1.X;
    Y = p2.Y - p1.Y;
    Z = p2.Z - p1.Z;
}

//Operators overloads

Vector Vector::operator+(const Vector &other) const {
    return {X + other.X, Y + other.Y, Z + other.Z};
}

Vector Vector::operator-(const Vector &other) const {
    return {X - other.X, Y - other.Y, Z - other.Z};
}

Vector Vector::operator*(const float &scalar) const {
    return {X * scalar, Y * scalar, Z * scalar};
}

Vector Vector::operator/(const float &scalar) const {
    return {X / scalar, Y / scalar, Z / scalar};
}

//Equals operators overloads

Vector Vector::operator+=(const Vector &other) {
    X += other.X;
    Y += other.Y;
    Z += other.Z;
    return *this;
}

Vector Vector::operator-=(const Vector &other) {
    X -= other.X;
    Y -= other.Y;
    Z -= other.Z;
    return *this;
}

Vector Vector::operator*=(const float &scalar) {
    X *= scalar;
    Y *= scalar;
    Z *= scalar;
    return *this;
}

Vector Vector::operator/=(const float &scalar) {
    X /= scalar;
    Y /= scalar;
    Z /= scalar;
    return *this;
}

//Other methods

float Vector::DotProduct(const Vector &other) const{
    return X * other.X + Y * other.Y + Z * other.Z;
}

Vector Vector::CrossProduct(const Vector &other) const {
    return {Y * other.Z - Z * other.Y,
            Z * other.X - X * other.Z,
            X * other.Y - Y * other.X};
}

Vector Vector::Normalize() {
    float length = this->Length();
    if(length == 0) return *this;
    *this/=length;
    return *this;
}

float Vector::Length() const {
    return std::sqrt(X*X + Y*Y + Z*Z);
}

float Vector::Angle(Vector other) const {
    float dot = this->DotProduct(other);
    float lenSq1 = X*X + Y*Y + Z*Z;
    float lenSq2 = other.X*other.X + other.Y*other.Y + other.Z*other.Z;
    float angle = std::acos(dot/ std::sqrt(lenSq1 * lenSq2));
    return angle;
}

std::string Vector::toString() const {
    return "[" + std::to_string(X) + ", " + std::to_string(Y) + ", " + std::to_string(Z) + "]";
}
