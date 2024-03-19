#ifndef SFRAYTRACING_QUATERNION_H
#define SFRAYTRACING_QUATERNION_H

#include "Vector3.h"

class Quaternion {
public:
    float scalar{0.0f};
    Vector3 vector{0.0f, 0.0f, 0.0f};

    Quaternion();
    Quaternion(float scalar, const Vector3& vector);
    Quaternion(const Quaternion& quaternion);

    Quaternion& operator=(const Quaternion& quaternion);
    Quaternion operator+(const Quaternion& quaternion) const;
    Quaternion operator-(const Quaternion& quaternion) const;
    Quaternion operator*(const Quaternion& quaternion) const;
    Quaternion operator*(float f) const;

    Quaternion operator+=(const Quaternion& quaternion);
    Quaternion operator-=(const Quaternion& quaternion);
    Quaternion operator*=(const Quaternion& quaternion);
    Quaternion operator*=(float f);

    [[nodiscard]] float norm() const;

    Quaternion normalize();
    [[nodiscard]] Quaternion normalized() const;

    [[nodiscard]] Quaternion conjugate() const;
    [[nodiscard]] Quaternion inverse() const;
    Quaternion convertToUnitNorm();

    [[nodiscard]] std::string toString() const;

};

#endif //SFRAYTRACING_QUATERNION_H
