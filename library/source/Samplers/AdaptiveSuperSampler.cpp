#include "Samplers/AdaptiveSuperSampler.h"

using namespace std;

AdaptiveSuperSampler::AdaptiveSuperSampler() : Sampler(4) {};

AdaptiveSuperSampler::AdaptiveSuperSampler(int samplingResolution) : Sampler(samplingResolution) {}

Color AdaptiveSuperSampler::samplePixel(int x, int y) {

    Vector3 upper_left = upperLeftViewportCorner +
                         pixelDeltaU * x +
                         pixelDeltaV * y;

    return sampleRegion(upper_left, pixelDeltaU, pixelDeltaV, 1);
}

Color AdaptiveSuperSampler::sampleRegion(Vector3 regionLocation, Vector3 deltaX, Vector3 deltaY, int depth) {
    Color center;
    Color colors[4];

    Vector3 half_delta_x = deltaX * 0.5;
    Vector3 half_delta_y = deltaY * 0.5;

    center = samplePoint(regionLocation + half_delta_x + half_delta_y);
    colors[0] = samplePoint(regionLocation);
    colors[1] = samplePoint(regionLocation + deltaX);
    colors[2] = samplePoint(regionLocation + deltaY);
    colors[3] = samplePoint(regionLocation + deltaX + deltaY);

    if(depth >= SamplingResolution_){
        return Color::getAverageColor(colors, 4);
    }

    if(center != colors[0]) colors[0] = sampleRegion(regionLocation, deltaX * 0.5, deltaY * 0.5, depth + 1);
    if(center != colors[1]) colors[1] = sampleRegion(regionLocation + deltaX, deltaX * 0.5, deltaY * 0.5, depth + 1);
    if(center != colors[2]) colors[2] = sampleRegion(regionLocation + deltaY, deltaX * 0.5, deltaY * 0.5, depth + 1);
    if(center != colors[3]) colors[3] = sampleRegion(regionLocation + deltaX +deltaY, deltaX * 0.5, deltaY * 0.5, depth + 1);

    return Color::getAverageColor(colors, 4);

}
