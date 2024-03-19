#ifndef SFRAYTRACING_MATRIX4X4_H
#define SFRAYTRACING_MATRIX4X4_H

#include "Vector3.h"

class Matrix4x4{
public:
    float entries[16] = {};

    Matrix4x4();
    Matrix4x4(float e0, float e4, float e8, float e12,
              float e1, float e5, float e9, float e13,
              float e2, float e6, float e10, float e14,
              float e3, float e7, float e11, float e15);
    Matrix4x4(const Matrix4x4& m);
    explicit Matrix4x4(const float * pF);

    static Matrix4x4 identity();
    static Matrix4x4 getTranslateMatrix(float x, float y, float z);
    static Matrix4x4 getScaleMatrix(float x, float y, float z);
    static Matrix4x4 getRotateMatrix(float angle, const Vector3& axis);
    static Matrix4x4 getRotateXMatrix(float angle);
    static Matrix4x4 getRotateYMatrix(float angle);
    static Matrix4x4 getRotateZMatrix(float angle);

    Matrix4x4 operator+(const Matrix4x4& m) const;
    Matrix4x4 operator-(const Matrix4x4& m) const;
    Matrix4x4 operator*(const Matrix4x4& m) const;

    Matrix4x4 operator*(float f) const;

    [[nodiscard]] Matrix4x4 transpose() const;
    Matrix4x4 inverse();

    [[nodiscard]] Vector3 transform(const Vector3& v) const;

};

#endif //SFRAYTRACING_MATRIX4X4_H
