#include <cmath>
#include <cfloat>
#include "Vector3.h"
#include "Quaternion.h"
#include "Helpers/MathHelper.h"


Vector3::Vector3() = default;

Vector3::Vector3(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

Vector3::Vector3(const Vector3& p1, const Vector3& p2) {
    x = p2.x - p1.x;
    y = p2.y - p1.y;
    z = p2.z - p1.z;
}

Vector3 Vector3::random() {
    return {MathHelper::randomFloat(), MathHelper::randomFloat(), MathHelper::randomFloat()};
}

Vector3 Vector3::random(float min, float max) {
    return {MathHelper::randomFloat(min, max), MathHelper::randomFloat(min, max), MathHelper::randomFloat(min, max)};
}

Vector3 Vector3::randomInUnitSphere() {
    while(true){
        auto p = Vector3::random();
        if(p.lengthSquared() < 1){
            return p;
        }
    }
}

Vector3 Vector3::randomUnitVector() {
    return randomInUnitSphere().normalized();
}

Vector3 Vector3::randomOnHemisphere(const Vector3 &normal) {
    Vector3 unit_sphere_vector = randomUnitVector();
    if(unit_sphere_vector.dotProduct(normal) > 0.0){
        return unit_sphere_vector;
    } else {
        return -unit_sphere_vector;
    }
}

//Operators overloads

Vector3 Vector3::operator+(const Vector3 &other) const {
    return {x + other.x, y + other.y, z + other.z};
}

Vector3 Vector3::operator-(const Vector3 &other) const {

    return {x - other.x, y - other.y, z - other.z};
}

Vector3 Vector3::operator*(const float &scalar) const {
    return {x * scalar, y * scalar, z * scalar};
}

Vector3 Vector3::operator/(const float &scalar) const {
    return {x / scalar, y / scalar, z / scalar};
}

//Equals operators overloads

Vector3 Vector3::operator+=(const Vector3 &other) {
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
}

Vector3 Vector3::operator-=(const Vector3 &other) {
    x -= other.x;
    y -= other.y;
    z -= other.z;
    return *this;
}

Vector3 Vector3::operator*=(float scalar) {
    x *= scalar;
    y *= scalar;
    z *= scalar;
    return *this;
}

Vector3 Vector3::operator/=(float scalar) {
    x /= scalar;
    y /= scalar;
    z /= scalar;
    return *this;
}

bool Vector3::operator==(const Vector3 &other) const {
    return std::fabs(x - other.x) <= FLT_EPSILON &&
            std::fabs(y - other.y) <= FLT_EPSILON &&
            std::fabs(z - other.z) <= FLT_EPSILON;
}

Vector3 Vector3::operator-() {
    x = -x;
    y = -y;
    z = -z;
    return *this;
}

//Other methods

float Vector3::dotProduct(const Vector3 &other) const{
    return x * other.x + y * other.y + z * other.z;
}

Vector3 Vector3::crossProduct(const Vector3 &other) const {
    return {y * other.z - z * other.y,
            z * other.x - x * other.z,
            x * other.y - y * other.x};
}

Vector3 Vector3::normalize() {
    float length = this->length();
    if(length == 0) return *this;
    *this/=length;
    return *this;
}

Vector3 Vector3::normalized() const {
    float length = this->length();
    if(length == 0) return *this;
    return *this/length;
}

float Vector3::length() const {
    return std::sqrt(lengthSquared());
}

float Vector3::lengthSquared() const {
    return x * x + y * y + z * z;
}

float Vector3::angle(Vector3 other) const {
    float dot = this->dotProduct(other);
    float lenSq1 = x * x + y * y + z * z;
    float lenSq2 = other.x * other.x + other.y * other.y + other.z * other.z;
    float angle = std::acos(dot/ std::sqrt(lenSq1 * lenSq2));
    return angle;
}

std::string Vector3::toString() const {
    return "[" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + "]";
}

Vector3 Vector3::rotateAroundAngleAndAxis(float angle, Vector3 &axis) const {
    Quaternion pure = {0, *this};
    axis.normalize();

    Quaternion q = {angle, axis};
    q = q.convertToUnitNorm();
    Quaternion qInv = q.inverse();
    Quaternion rotatedVector = q * pure * qInv;

    return rotatedVector.vector;
}
