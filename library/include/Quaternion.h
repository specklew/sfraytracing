#ifndef SFRAYTRACING_QUATERNION_H
#define SFRAYTRACING_QUATERNION_H

#include "Vector.h"

class Quaternion {
public:
    float scalar{0.0f};
    Vector vector{0.0f, 0.0f, 0.0f};

    Quaternion();
    Quaternion(float scalar, const Vector& vector);
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

    [[nodiscard]] float Norm() const;

    Quaternion Normalize();
    [[nodiscard]] Quaternion Normalized() const;

    [[nodiscard]] Quaternion Conjugate() const;
    [[nodiscard]] Quaternion Inverse() const;
    Quaternion convertToUnitNorm();

    [[nodiscard]] std::string toString() const;

};

#endif //SFRAYTRACING_QUATERNION_H
