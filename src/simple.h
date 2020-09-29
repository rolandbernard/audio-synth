#ifndef _SIMPLE_H_
#define _SIMPLE_H_

typedef struct {
    int sample_rate;
    float frequency;
    float skew;
} SimpleWaveSynthParameters;

float simpleSineWaveSynth(SimpleWaveSynthParameters* params, long sample);

float simpleSquareWaveSynth(SimpleWaveSynthParameters* params, long sample);

float simpleTriangleWaveSynth(SimpleWaveSynthParameters* params, long sample);

#endif