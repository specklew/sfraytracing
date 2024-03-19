#ifndef SFRAYTRACING_VECTOR_H
#define SFRAYTRACING_VECTOR_H


#include <string>

class Vector{
public:
    Vector();
    Vector(float x, float y, float z);
    Vector(const Vector& p1, const Vector& p2);
    float x{};
    float y{};
    float z{};

    Vector operator+(const Vector& other) const;
    Vector operator-(const Vector& other) const;
    Vector operator*(const float& scalar) const;
    Vector operator/(const float& scalar) const;

    Vector operator+=(const Vector& other);
    Vector operator-=(const Vector& other);
    Vector operator*=(float scalar);
    Vector operator/=(float scalar);

    [[nodiscard]] float dotProduct(const Vector& other) const;
    [[nodiscard]] Vector crossProduct(const Vector& other) const;

    Vector normalize();
    Vector normalized() const;

    [[nodiscard]] float length() const;
    [[nodiscard]] float angle(Vector other) const;

    Vector rotateAroundAngleAndAxis(float angle, Vector& axis) const;

    [[nodiscard]] std::string toString() const;
};

#endif //SFRAYTRACING_VECTOR_H