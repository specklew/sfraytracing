#ifndef SFRAYTRACING_VECTOR3_H
#define SFRAYTRACING_VECTOR3_H


#include <string>

class Vector3{
public:
    double x{};
    double y{};
    double z{};

    Vector3();
    Vector3(double x, double y, double z);
    Vector3(const Vector3& p1, const Vector3& p2);

    static Vector3 random();
    static Vector3 random(double min, double max);
    static Vector3 randomInUnitSphere();
    static Vector3 randomUnitVector();
    static Vector3 randomOnHemisphere(const Vector3& normal);

    Vector3 operator+(const Vector3& other) const;
    Vector3 operator-(const Vector3& other) const;
    Vector3 operator*(const double& scalar) const;
    Vector3 operator/(const double& scalar) const;

    Vector3 operator+=(const Vector3& other);
    Vector3 operator-=(const Vector3& other);
    Vector3 operator*=(double scalar);
    Vector3 operator/=(double scalar);

    bool operator==(const Vector3& other) const;

    Vector3 operator-();

    [[nodiscard]] double dotProduct(const Vector3& other) const;
    [[nodiscard]] Vector3 crossProduct(const Vector3& other) const;

    Vector3 normalize();
    [[nodiscard]] Vector3 normalized() const;

    Vector3 reflect(const Vector3& normal);

    [[nodiscard]] double length() const;
    [[nodiscard]] double lengthSquared() const;
    [[nodiscard]] double angle(Vector3 other) const;

    [[nodiscard]] bool isNearZero() const;

    Vector3 rotateAroundAngleAndAxis(double angle, Vector3& axis) const;

    [[nodiscard]] std::string toString() const;
};

#endif //SFRAYTRACING_VECTOR3_H