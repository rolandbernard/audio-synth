
#include <math.h>
#include "simple.h"

#define PI 3.14159265358979323846

void simpleSineWaveSynth(SynthEnviormentData* env, SynthInstrumentData* instrument, SynthNoteData* note, int len, float* out) {
    for(int i = 0; i < len; i++) {
        out[i] += sinf(2 * PI * note->frequency * (note->sample_from_noteon + i) / env->sample_rate);
    }
}

void simpleSquareWaveSynth(SynthEnviormentData* env, SimpleWaveSynthInstrumentData* instrument, SynthNoteData* note, int len, float* out) {
    float intg;
    float frac;
    for(int i = 0; i < len; i++) {
        frac = modff(note->frequency * (note->sample_from_noteon + i) / env->sample_rate, &intg);
        out[i] += frac < instrument->skew ? -1.0 : 1.0;
    }
}

void simpleTriangleWaveSynth(SynthEnviormentData* env, SimpleWaveSynthInstrumentData* instrument, SynthNoteData* note, int len, float* out) {
    float intg;
    float frac;
    for(int i = 0; i < len; i++) {
        frac = modff(note->frequency * (note->sample_from_noteon + i) / env->sample_rate, &intg);
        out[i] += (frac < instrument->skew) ? (-1.0 + 2 * frac / instrument->skew) : (-1.0 + 2 * (1 - frac) / (1 - instrument->skew));
    }
}
