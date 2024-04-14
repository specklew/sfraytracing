#include <cmath>
#include <cfloat>
#include "Vector3.h"
#include "Quaternion.h"
#include "Helpers/MathHelper.h"


Vector3::Vector3() = default;

Vector3::Vector3(precision x, precision y, precision z) {
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
    return {MathHelper::randomPrecision(), MathHelper::randomPrecision(), MathHelper::randomPrecision()};
}

Vector3 Vector3::random(precision min, precision max) {
    return {MathHelper::randomPrecision(min, max), MathHelper::randomPrecision(min, max), MathHelper::randomPrecision(min, max)};
}

Vector3 Vector3::randomInUnitSphere() {
    while(true){
        auto p = Vector3::random(-1, 1);
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
    if(unit_sphere_vector.dotProduct(normal) > 0){
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

Vector3 Vector3::operator*(const precision &scalar) const {
    return {x * scalar, y * scalar, z * scalar};
}

Vector3 Vector3::operator/(const precision &scalar) const {
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

Vector3 Vector3::operator*=(precision scalar) {
    x *= scalar;
    y *= scalar;
    z *= scalar;
    return *this;
}

Vector3 Vector3::operator/=(precision scalar) {
    x /= scalar;
    y /= scalar;
    z /= scalar;
    return *this;
}

bool Vector3::operator==(const Vector3 &other) const {
    return std::fabs(x - other.x) <= epsilon &&
            std::fabs(y - other.y) <= epsilon &&
            std::fabs(z - other.z) <= epsilon;
}

Vector3 Vector3::operator-() {
    x = -x;
    y = -y;
    z = -z;
    return *this;
}

//Other methods

precision Vector3::dotProduct(const Vector3 &other) const{
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

precision Vector3::length() const {
    return std::sqrt(lengthSquared());
}

precision Vector3::lengthSquared() const {
    return x * x + y * y + z * z;
}

precision Vector3::angle(Vector3 other) const {
    float dot = this->dotProduct(other);
    float lenSq1 = x * x + y * y + z * z;
    float lenSq2 = other.x * other.x + other.y * other.y + other.z * other.z;
    float angle = std::acos(dot/ std::sqrt(lenSq1 * lenSq2));
    return angle;
}

bool Vector3::isNearZero() const {
    return (std::fabs(x) < epsilon &&
            std::fabs(y) < epsilon &&
            std::fabs(z) < epsilon);
}

std::string Vector3::toString() const {
    return "[" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + "]";
}

Vector3 Vector3::rotateAroundAngleAndAxis(precision angle, Vector3 &axis) const {
    Quaternion pure = {0, *this};
    axis.normalize();

    Quaternion q = {angle, axis};
    q = q.convertToUnitNorm();
    Quaternion qInv = q.inverse();
    Quaternion rotatedVector = q * pure * qInv;

    return rotatedVector.vector;
}

Vector3 Vector3::reflect(const Vector3 &normal) {
    *this = *this - normal * 2 * (*this).dotProduct(normal);
    return *this;
}

Vector3 Vector3::reflected(const Vector3 &normal) const {
    return *this - normal * 2 * (*this).dotProduct(normal);
}

Vector3 Vector3::refract(const Vector3 &normal, precision eta_over_eta) {
    precision one = 1;
    precision cos_theta = std::min(dotProduct(normal), one);

    Vector3 perpendicular = (*this + normal * cos_theta) * eta_over_eta;
    Vector3 parallel = -(normal * std::sqrt(std::abs(one - perpendicular.lengthSquared())));

    *this = perpendicular + parallel;
    return *this;
}

Vector3 Vector3::refracted(const Vector3 &normal, precision eta_over_eta) const {
    precision one = 1;
    precision cos_theta = std::min(-this->dotProduct(normal), one);

    Vector3 perpendicular = (*this + normal * cos_theta) * eta_over_eta;
    Vector3 parallel = -(normal * std::sqrt(std::abs(one - perpendicular.lengthSquared())));

    return perpendicular + parallel;
}
