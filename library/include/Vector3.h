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

    static Vector3 random();
    static Vector3 random(float min, float max);
    static Vector3 randomInUnitSphere();
    static Vector3 randomUnitVector();
    static Vector3 randomOnHemisphere(const Vector3& normal);

    Vector3 operator+(const Vector3& other) const;
    Vector3 operator-(const Vector3& other) const;
    Vector3 operator*(const float& scalar) const;
    Vector3 operator/(const float& scalar) const;

    Vector3 operator+=(const Vector3& other);
    Vector3 operator-=(const Vector3& other);
    Vector3 operator*=(float scalar);
    Vector3 operator/=(float scalar);

    bool operator==(const Vector3& other) const;

    Vector3 operator-();

    [[nodiscard]] float dotProduct(const Vector3& other) const;
    [[nodiscard]] Vector3 crossProduct(const Vector3& other) const;

    Vector3 normalize();
    [[nodiscard]] Vector3 normalized() const;

    Vector3 reflect(const Vector3& normal);

    [[nodiscard]] float length() const;
    [[nodiscard]] float lengthSquared() const;
    [[nodiscard]] float angle(Vector3 other) const;

    [[nodiscard]] bool isNearZero() const;

    Vector3 rotateAroundAngleAndAxis(float angle, Vector3& axis) const;

    [[nodiscard]] std::string toString() const;
};

template<>
struct std::hash<Vector3>{
    std::size_t operator()(const Vector3& vector) const{
        using std::size_t;
        using std::hash;

        // Compute individual hash values for first, second and third
        // http://stackoverflow.com/a/1646913/126995
        std::size_t res = 17;
        res = res * 31 + std::hash<float>{}(vector.x);
        res = res * 31 + std::hash<float>{}(vector.y);
        res = res * 31 + std::hash<float>{}(vector.z);

        return res;
    }
};

#endif //SFRAYTRACING_VECTOR3_H