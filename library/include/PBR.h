#ifndef SF_RAYTRACING_PBR_H
#define SF_RAYTRACING_PBR_H

#include "Precision.h"
#include "Vector3.h"
#include "Helpers/MathHelper.h"
#include "Color.h"
#include <cmath>

precision distributionGGX(Vector3 normal, Vector3 halfway, precision roughness){
    precision a = roughness * roughness;
    precision a2 = a * a;
    precision normal_dot_half = std::max(normal.dot(halfway), precision(0));
    precision normal_dot_half_sq = normal_dot_half * normal_dot_half;

    precision nom   = a2;
    precision denominator = (normal_dot_half_sq * (a2 - 1) + 1);
    denominator = pi * denominator * denominator;

    return nom / denominator;
}

precision geometrySchlickGGX(precision normalDotView, precision roughness)
{
    precision r = roughness + 1;

    // K is remapping of roughness (a) for either direct lightning or IBL lightning.
    // Kdirect = (a + 1)^2 / 8.
    // Kibl = a^2 / 2.
    precision k = (r * r) / 8;

    precision normal = normalDotView;
    precision denominator = normalDotView * (1 - k) + k;

    return normal / denominator;
}

precision geometrySmith(Vector3 normal, Vector3 view, Vector3 light, precision roughness)
{
    precision normal_dot_vec = std::max(normal.dot(view), precision(0));
    precision normal_dot_light = std::max(normal.dot(light), precision(0));
    precision ggx2 = geometrySchlickGGX(normal_dot_vec, roughness);
    precision ggx1 = geometrySchlickGGX(normal_dot_light, roughness);

    return ggx1 * ggx2;
}

// Approximation of fresnel equation.
Color fresnelSchlick(precision cosTheta, const Color& baseReflectivity)
{
    precision one_min_cos_theta = 1 - cosTheta;
    return baseReflectivity + (-baseReflectivity + 1.0) * std::pow(
            MathHelper::clamp(one_min_cos_theta, precision(0), precision(1)),
            precision(5));
}

precision anisotropicGGX(Vector3 halfway, Vector3 normal, Vector3 x, Vector3 y, precision ax, precision ay){
    precision first = precision(1) / (pi * ax * ay);
    precision n_dot_h = normal.dot(halfway);
    precision n_dot_h2 = n_dot_h * n_dot_h;
    precision xh = pow((x.dot(halfway)), 2) / pow(ax, 2);
    precision yh = pow(y.dot(halfway), 2) / pow(ay, 2);
    precision second = precision(1) / pow(xh + yh + n_dot_h2, 2);
    return first * second;
}

Color computeReflectance(Vector3 N, Vector3 Ve, const Color& baseReflectivity, const Color& albedo, Vector3 L, Vector3 H, const Color& lightColor,
                           precision intensity, precision metallic, precision roughness, precision anisotropy)
{
    Color radiance = lightColor * intensity; //Incoming Radiance

    // cook-torrance brdf
    precision D = distributionGGX(N, H, roughness);
    precision G = geometrySmith(N, Ve, L, roughness);
    Color F = fresnelSchlick(std::max(H.dot(Ve), precision(0)), baseReflectivity);

    if(anisotropy > 0){
        Vector3 tangent = Vector3(0,0,1).cross(N).normalized();
        Vector3 bi_tangent = N.cross(tangent);
        precision an = anisotropicGGX(H, N, tangent, bi_tangent, 0.05, 0.02);
        D = MathHelper::lerp(D, an, anisotropy);
    }

    const Color& kS = F;
    Color kD = Color(1.0) - kS;
    kD *= (1.0 - metallic);

    Color nominator = F * D * G;
    precision denominator = 4 * std::max(N.dot(Ve), precision(0)) * std::max(N.dot(L), precision(0)) + 0.00001/* avoid divide by zero*/;
    Color specular = nominator / denominator;


    // add to outgoing radiance Lo
    precision n_dot_l = std::max(N.dot(L), precision(0));
    Color diffuse_radiance = (albedo) * kD / pi;

    return (diffuse_radiance + specular) * radiance * n_dot_l;
}

#endif //SF_RAYTRACING_PBR_H
