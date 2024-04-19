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

Vector3::Vector3(const precision& scalar) {
    x = scalar;
    y = scalar;
    z = scalar;
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
    if(unit_sphere_vector.dot(normal) > 0){
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

precision Vector3::dot(const Vector3 &other) const{
    return x * other.x + y * other.y + z * other.z;
}

Vector3 Vector3::cross(const Vector3 &other) const {
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
    float dot = this->dot(other);
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
    *this = *this - normal * 2 * (*this).dot(normal);
    return *this;
}

Vector3 Vector3::reflected(const Vector3 &normal) const {
    return *this - normal * 2 * (*this).dot(normal);
}

Vector3 Vector3::refract(const Vector3 &normal, precision eta_over_eta) {
    precision one = 1;
    precision cos_theta = std::min(dot(normal), one);

    Vector3 perpendicular = (*this + normal * cos_theta) * eta_over_eta;
    Vector3 parallel = -(normal * std::sqrt(std::abs(one - perpendicular.lengthSquared())));

    *this = perpendicular + parallel;
    return *this;
}

Vector3 Vector3::refracted(const Vector3 &normal, precision eta_over_eta) const {
    precision one = 1;
    precision cos_theta = std::min(-this->dot(normal), one);

    Vector3 perpendicular = (*this + normal * cos_theta) * eta_over_eta;
    Vector3 parallel = -(normal * std::sqrt(std::abs(one - perpendicular.lengthSquared())));

    return perpendicular + parallel;
}

Vector3 Vector3::operator*(const Vector3 &other) const {
    return {x * other.x, y * other.y, z * other.z};
}

Vector3 Vector3::operator/(const Vector3 &other) const {
    return {x / other.x, y / other.y, z / other.z};
}

// BRDF Helper functions.

precision DistributionGGX(Vector3 normal, Vector3 halfway, precision roughness){
    precision a = roughness*roughness;
    precision a2 = a*a;
    precision normal_dot_half = std::max(normal.dot(halfway), precision(0));
    precision normal_dot_half_sq = normal_dot_half * normal_dot_half;

    precision nom   = a2;
    precision denominator = (normal_dot_half_sq * (a2 - 1) + 1);
    denominator = pi * denominator * denominator;

    return nom / denominator;
}

precision GeometrySchlickGGX(precision normalDotView, precision roughness)
{
    precision r = roughness + 1;
    precision k = (r * r) / 8;

    precision normal = normalDotView;
    precision denominator = normalDotView * (1 - k) + k;

    return normal / denominator;
}

precision GeometrySmith(Vector3 normal, Vector3 view, Vector3 light, precision roughness)
{
    precision normal_dot_vec = std::max(normal.dot(view), precision(0));
    precision normal_dot_light = std::max(normal.dot(light), precision(0));
    precision ggx2 = GeometrySchlickGGX(normal_dot_vec, roughness);
    precision ggx1 = GeometrySchlickGGX(normal_dot_light, roughness);

    return ggx1 * ggx2;
}

Vector3 fresnelSchlick(precision cosTheta, Vector3 F0)
{
    precision one_min_cos_theta = 1 - cosTheta;
    return F0 + (-F0 + 1.0) * std::pow(
            MathHelper::clamp(one_min_cos_theta, precision(0), precision(1)),
            precision(5));
}

Vector3 computeReflectance(Vector3 N, Vector3 Ve, Vector3 F0, Vector3 albedo, Vector3 L, Vector3 H, Vector3 light_col,
                           precision intensity, precision metallic, precision roughness)
{
    Vector3 radiance =  light_col * intensity; //Incoming Radiance

    // cook-torrance brdf
    float NDF = DistributionGGX(N, H, roughness);
    float G = GeometrySmith(N, Ve, L,roughness);
    Vector3 F = fresnelSchlick(std::max(H.dot(Ve), precision(0)), F0);

    Vector3 kS = F;
    Vector3 kD = Vector3(1.0) - kS;
    kD *= 1.0 - metallic;

    Vector3 nominator =  F * NDF * G;
    float denominator = 4 * std::max(N.dot(Ve), precision(0)) * std::max(N.dot(L), precision(0)) + 0.00001/* avoid divide by zero*/;
    Vector3 specular = nominator / denominator;


    // add to outgoing radiance Lo
    float NdotL = std::max(N.dot( L), precision(0));
    Vector3 diffuse_radiance = (albedo) * kD / pi;

    return (diffuse_radiance + specular) * radiance * NdotL;
}