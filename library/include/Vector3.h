#ifndef SFRAYTRACING_VECTOR3_H
#define SFRAYTRACING_VECTOR3_H


#include <string>
#include "Precision.h"
class Vector3{
public:
    precision x{};
    precision y{};
    precision z{};

    Vector3();
    Vector3(precision x, precision y, precision z);
    Vector3(const Vector3& p1, const Vector3& p2);
    Vector3(const precision& scalar);

    static Vector3 random();
    static Vector3 random(precision min, precision max);
    static Vector3 randomInUnitSphere();
    static Vector3 randomUnitVector();
    static Vector3 randomOnHemisphere(const Vector3& normal);

    Vector3 operator+(const Vector3& other) const;
    Vector3 operator-(const Vector3& other) const;
    Vector3 operator*(const Vector3& other) const;
    Vector3 operator/(const Vector3& other) const;
    Vector3 operator*(const precision& scalar) const;
    Vector3 operator/(const precision& scalar) const;

    Vector3 operator+=(const Vector3& other);
    Vector3 operator-=(const Vector3& other);
    Vector3 operator*=(precision scalar);
    Vector3 operator/=(precision scalar);

    bool operator==(const Vector3& other) const;

    Vector3 operator-();

    [[nodiscard]] precision dot(const Vector3& other) const;
    [[nodiscard]] Vector3 cross(const Vector3& other) const;

    Vector3 normalize();
    [[nodiscard]] Vector3 normalized() const;

    Vector3 reflect(const Vector3& normal);
    [[nodiscard]] Vector3 reflected(const Vector3& normal) const;
    Vector3 refract(const Vector3& normal, precision eta_over_eta);
    [[nodiscard]] Vector3 refracted(const Vector3& normal, precision eta_over_eta) const;

    [[nodiscard]] precision length() const;
    [[nodiscard]] precision lengthSquared() const;
    [[nodiscard]] precision angle(Vector3 other) const;

    [[nodiscard]] bool isNearZero() const;

    Vector3 rotateAroundAngleAndAxis(precision angle, Vector3& axis) const;

    [[nodiscard]] std::string toString() const;
};

#endif //SFRAYTRACING_VECTOR3_H