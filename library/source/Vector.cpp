#include "../include/Vector.h"

Vector::Vector() = default;

Vector::Vector(float x, float y, float z) {
    X = x;
    Y = y;
    Z = z;
}

Vector Vector::operator+(const Vector &other) const {
    return Vector(X + other.X, Y + other.Y, Z + other.Z);
}

Vector Vector::operator-(const Vector &other) const {
    return Vector(X - other.X, Y - other.Y, Z - other.Z);
}

float Vector::DotProduct(const Vector &other) const{
    return X * other.X + Y * other.Y + Z * other.Z;
}

Vector Vector::CrossProduct(const Vector &other) const {
    return Vector(
            Y * other.Z - Z * other.Y,
            X * other.Z - Z * other.X,
            X * other.Y - Y * other.X);
}
