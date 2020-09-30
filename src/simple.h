#ifndef _SIMPLE_H_
#define _SIMPLE_H_

typedef struct {
    int sample_rate;
    float skew;
} SimpleWaveSynthParameters;

float simpleSineWaveSynth(SimpleWaveSynthParameters* params, float frequency, long sample);

float simpleSquareWaveSynth(SimpleWaveSynthParameters* params, float frequency, long sample);

float simpleTriangleWaveSynth(SimpleWaveSynthParameters* params, float frequency, long sample);

#endif