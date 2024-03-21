#include <cmath>
#include "Matrix4x4.h"

Matrix4x4::Matrix4x4() = default;

Matrix4x4::Matrix4x4(float e0, float e4, float e8, float e12,
                     float e1, float e5, float e9, float e13,
                     float e2,float e6, float e10, float e14,
                     float e3, float e7, float e11, float e15) {

    entries[0] = e0;
    entries[1] = e1;
    entries[2] = e2;
    entries[3] = e3;
    entries[4] = e4;
    entries[5] = e5;
    entries[6] = e6;
    entries[7] = e7;
    entries[8] = e8;
    entries[9] = e9;
    entries[10] = e10;
    entries[11] = e11;
    entries[12] = e12;
    entries[13] = e13;
    entries[14] = e14;
    entries[15] = e15;

}

Matrix4x4::Matrix4x4(const Matrix4x4 &m) {
    memcpy(entries, m.entries, sizeof(entries));
}

Matrix4x4::Matrix4x4(const float *pF) {
    memcpy(entries, pF, sizeof(entries));
}

Matrix4x4 Matrix4x4::identity() {
    return {1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1};
}

Matrix4x4 Matrix4x4::getTranslateMatrix(float x, float y, float z) {
    return {1, 0, 0, x,
            0, 1, 0, y,
            0, 0, 1, z,
            0, 0, 0, 1};
}

Matrix4x4 Matrix4x4::getScaleMatrix(float x, float y, float z) {
    return {x, 0, 0, 0,
            0, y, 0, 0,
            0, 0, z, 0,
            0, 0, 0, 1};
}

Matrix4x4 Matrix4x4::getRotateMatrix(float angle, const Vector3 &axis) {
    float c = std::cos(angle);
    float s = std::sin(angle);
    float t = 1 - c;

    float x = axis.x;
    float y = axis.y;
    float z = axis.z;

    return {t * x * x + c, t * x * y - s * z, t * x * z + s * y, 0,
            t * x * y + s * z, t * y * y + c, t * y * z - s * x, 0,
            t * x * z - s * y, t * y * z + s * x, t * z * z + c, 0,
            0, 0, 0, 1};
}

Matrix4x4 Matrix4x4::getRotateXMatrix(float angle) {
    float c = std::cos(angle);
    float s = std::sin(angle);
    return {1, 0, 0, 0,
            0, c, -s, 0,
            0, s, c, 0,
            0, 0, 0, 1};
}

Matrix4x4 Matrix4x4::getRotateYMatrix(float angle) {
    float c = std::cos(angle);
    float s = std::sin(angle);
    return {c, 0, s, 0,
            0, 1, 0, 0,
            -s, 0, c, 0,
            0, 0, 0, 1};
}

Matrix4x4 Matrix4x4::getRotateZMatrix(float angle) {
    float c = std::cos(angle);
    float s = std::sin(angle);
    return {c, -s, 0, 0,
            s, c, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1};
}

Matrix4x4 Matrix4x4::operator+(const Matrix4x4 &m) const {
    Matrix4x4 result;
    for (int i = 0; i < 16; i++) {
        result.entries[i] = entries[i] + m.entries[i];
    }
    return result;
}

Matrix4x4 Matrix4x4::operator-(const Matrix4x4 &m) const {
    Matrix4x4 result;
    for (int i = 0; i < 16; i++) {
        result.entries[i] = entries[i] - m.entries[i];
    }
    return result;
}

//TODO: Optimize the when the bottom row is (0, 0, 0, 1).
Matrix4x4 Matrix4x4::operator*(const Matrix4x4 &m) const {
    Matrix4x4 result;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            for (int k = 0; k < 4; k++) {
                result.entries[i * 4 + j] += entries[i * 4 + k] * m.entries[k * 4 + j];
            }
        }
    }
    return result;
}

Matrix4x4 Matrix4x4::operator*(float f) const {
    Matrix4x4 result;
    for (int i = 0; i < 16; i++) {
        result.entries[i] = entries[i] * f;
    }
    return result;
}

Matrix4x4 Matrix4x4::transpose() const {
    Matrix4x4 result;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            result.entries[i * 4 + j] = entries[j * 4 + i];
        }
    }
    return result;
}

Matrix4x4 Matrix4x4::inverse() {
    float t1 = entries[0] * entries[4];
    float t2 = entries[0] * entries[7];
    float t3 = entries[3] * entries[1];
    float t4 = entries[6] * entries[1];
    float t5 = entries[3] * entries[2];
    float t6 = entries[6] * entries[2];

    float det = t1 * entries[8] - t2 * entries[5] - t3 * entries[8] + t4 * entries[5] + t5 * entries[7] - t6 * entries[4];

    if (det == 0) {
        return *this;
    }

    float invDet = 1.0f / det;

    float m0 = (entries[4] * entries[8] - entries[7] * entries[5]) * invDet;
    float m3 = -(entries[3] * entries[8] - entries[6] * entries[5]) * invDet;
    float m6 = (entries[3] * entries[7] - entries[6] * entries[4]) * invDet;
    float m1 = -(entries[1] * entries[7] - entries[2] * entries[4]) * invDet;
    float m4 = (entries[0] * entries[8] - t6) * invDet;
    float m7 = -(t2 - t4) * invDet;
    float m2 = (entries[1] * entries[5] - entries[2] * entries[4]) * invDet;
    float m5 = -(entries[0] * entries[4] - t5) * invDet;
    float m8 = (t1 - t3) * invDet;

    entries[0] = m0;
    entries[1] = m1;
    entries[2] = m2;
    entries[3] = m3;
    entries[4] = m4;
    entries[5] = m5;
    entries[6] = m6;
    entries[7] = m7;
    entries[8] = m8;

    return *this;
}

Vector3 Matrix4x4::transform(const Vector3 &v) const {
    return {entries[0] * v.x + entries[1] * v.y + entries[2] * v.z + entries[3],
            entries[4] * v.x + entries[5] * v.y + entries[6] * v.z + entries[7],
            entries[8] * v.x + entries[9] * v.y + entries[10] * v.z + entries[11]};
}
