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
    Vector operator*=(const float& scalar);
    Vector operator/=(const float& scalar);

    [[nodiscard]] float DotProduct(const Vector& other) const;
    [[nodiscard]] Vector CrossProduct(const Vector& other) const;

    Vector Normalize();
    Vector Normalized() const;

    [[nodiscard]] float Length() const;
    [[nodiscard]] float Angle(Vector other) const;

    [[nodiscard]] std::string toString() const;
};

#endif //SFRAYTRACING_VECTOR_H