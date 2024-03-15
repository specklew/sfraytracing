#include "../include/Vector.h"

Vector::Vector() = default;

Vector::Vector(float x, float y, float z) {
    X = x;
    Y = y;
    Z = z;
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
            X * other.Z - Z * other.X,
            X * other.Y - Y * other.X};
}
