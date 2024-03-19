#ifndef SFRAYTRACING_VECTOR3_H
#define SFRAYTRACING_VECTOR3_H


#include <string>

class Vector3{
public:
    float x{};
    float y{};
    float z{};

    Vector3();
    Vector3(float x, float y, float z);
    Vector3(const Vector3& p1, const Vector3& p2);

    Vector3 operator+(const Vector3& other) const;
    Vector3 operator-(const Vector3& other) const;
    Vector3 operator*(const float& scalar) const;
    Vector3 operator/(const float& scalar) const;

    Vector3 operator+=(const Vector3& other);
    Vector3 operator-=(const Vector3& other);
    Vector3 operator*=(float scalar);
    Vector3 operator/=(float scalar);

    [[nodiscard]] float dotProduct(const Vector3& other) const;
    [[nodiscard]] Vector3 crossProduct(const Vector3& other) const;

    Vector3 normalize();
    [[nodiscard]] Vector3 normalized() const;

    [[nodiscard]] float length() const;
    [[nodiscard]] float angle(Vector3 other) const;

    Vector3 rotateAroundAngleAndAxis(float angle, Vector3& axis) const;

    [[nodiscard]] std::string toString() const;
};

#endif //SFRAYTRACING_VECTOR3_H