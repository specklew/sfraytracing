#ifndef SF_RAYTRACING_SAMPLER_H
#define SF_RAYTRACING_SAMPLER_H

#include "Color.h"
#include "Vector3.h"
#include "Ray.h"
#include "vector"


class Sampler{
public:
    virtual ~Sampler();
    Sampler();
    Sampler(Vector3 center, Vector3 direction, int samplingResolution);

    Vector3 center;
    Vector3 direction;
    Vector3 upperLeftViewportCorner;
    Vector3 pixelDeltaU;
    Vector3 pixelDeltaV;

    bool isOrthographic{};

    [[nodiscard]] int GetMaximalSamplingResolution() const;
    void SetMaximalSamplingResolution(int maximalSamplingResolution);

    virtual Color sample(std::vector<Ray> rays) = 0;
    virtual std::vector<Vector3> calculateSamplePoints(int x, int y) = 0;

protected:
    int SamplingResolution_;
    float InvertedSamplingResolution_;
    Color *ColorBuffer_;
};


#endif //SF_RAYTRACING_SAMPLER_H
