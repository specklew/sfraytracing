#ifndef SFRAYTRACING_MATRIX4X4_H
#define SFRAYTRACING_MATRIX4X4_H

#include "Vector3.h"

class Matrix4x4{
public:
    precision entries[16] = {};

    Matrix4x4();
    Matrix4x4(precision e0, precision e4, precision e8, precision e12,
              precision e1, precision e5, precision e9, precision e13,
              precision e2, precision e6, precision e10, precision e14,
              precision e3, precision e7, precision e11, precision e15);
    Matrix4x4(const Matrix4x4& m);
    explicit Matrix4x4(const precision * pF);

    static Matrix4x4 identity();
    static Matrix4x4 getTranslateMatrix(precision x, precision y, precision z);
    static Matrix4x4 getScaleMatrix(precision x, precision y, precision z);
    static Matrix4x4 getRotateMatrix(precision angle, const Vector3& axis);
    static Matrix4x4 getRotateXMatrix(precision angle);
    static Matrix4x4 getRotateYMatrix(precision angle);
    static Matrix4x4 getRotateZMatrix(precision angle);

    Matrix4x4 operator+(const Matrix4x4& m) const;
    Matrix4x4 operator-(const Matrix4x4& m) const;
    Matrix4x4 operator*(const Matrix4x4& m) const;

    Matrix4x4 operator*(precision f) const;

    [[nodiscard]] Matrix4x4 transpose() const;
    Matrix4x4 inverse();

    [[nodiscard]] Vector3 transform(const Vector3& v) const;

};

#endif //SFRAYTRACING_MATRIX4X4_H
