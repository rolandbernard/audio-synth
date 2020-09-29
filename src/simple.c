
#include <math.h>
#include "simple.h"

#define PI 3.14159265358979323846

float simpleSineWaveSynth(SimpleWaveSynthParameters* params, long sample) {
    return sinf(2 * PI * params->frequency * sample / params->sample_rate);
}

float simpleSquareWaveSynth(SimpleWaveSynthParameters* params, long sample) {
    float intg;
    float frac = modff(params->frequency * sample / params->sample_rate, &intg);
    return frac < params->skew ? -1.0 : 1.0;
}

float simpleTriangleWaveSynth(SimpleWaveSynthParameters* params, long sample) {
    float intg;
    float frac = modff(params->frequency * sample / params->sample_rate, &intg);
    return (frac < params->skew) ? (-1.0 + 2 * frac / params->skew) : (-1.0 + 2 * (1-frac) / (1 - params->skew));
}
