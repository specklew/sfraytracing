#ifndef SFRAYTRACING_QUATERNION_H
#define SFRAYTRACING_QUATERNION_H

#include "Vector3.h"

class Quaternion {
public:
    precision scalar{0};
    Vector3 vector{0, 0, 0};

    Quaternion();
    Quaternion(precision scalar, const Vector3& vector);
    Quaternion(const Quaternion& quaternion);

    Quaternion& operator=(const Quaternion& quaternion);
    Quaternion operator+(const Quaternion& quaternion) const;
    Quaternion operator-(const Quaternion& quaternion) const;
    Quaternion operator*(const Quaternion& quaternion) const;
    Quaternion operator*(precision f) const;

    Quaternion operator+=(const Quaternion& quaternion);
    Quaternion operator-=(const Quaternion& quaternion);
    Quaternion operator*=(const Quaternion& quaternion);
    Quaternion operator*=(precision f);

    [[nodiscard]] precision norm() const;

    Quaternion normalize();
    [[nodiscard]] Quaternion normalized() const;

    [[nodiscard]] Quaternion conjugate() const;
    [[nodiscard]] Quaternion inverse() const;
    Quaternion convertToUnitNorm();

    [[nodiscard]] std::string toString() const;

};

#endif //SFRAYTRACING_QUATERNION_H
