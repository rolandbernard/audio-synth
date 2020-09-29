#ifndef _SIMPLE_H_
#define _SIMPLE_H_

typedef struct {
    int sample_rate;
    float frequency;
    float skew;
} SimpleWaveSynthParameters;

float simpleSineWaveSynth(SimpleWaveSynthParameters* params, int sample);

float simpleSquareWaveSynth(SimpleWaveSynthParameters* params, int sample);

float simpleTriangleWaveSynth(SimpleWaveSynthParameters* params, int sample);

#endif