
#include <math.h>
#include "simple.h"

#define PI 3.14159265358979323846

void simpleSineWaveSynth(SynthEnviormentData* env, SynthInstrumentData* instrument, SynthNoteData* note, int len, float* out) {
    if(note->sample_from_noteoff < 0) {
        for(int i = 0; i < len; i++) {
            if(note->sample_from_noteon + i >= 0) {
                out[i] += sinf(2 * PI * note->frequency * (note->sample_from_noteon + i) / env->sample_rate);
            }
        }
    } else {
        note->reached_end = true;
    }
}

void simpleSquareWaveSynth(SynthEnviormentData* env, SimpleWaveSynthInstrumentData* instrument, SynthNoteData* note, int len, float* out) {
    if(note->sample_from_noteoff < 0) {
        float intg;
        float frac;
        for(int i = 0; i < len; i++) {
            if(note->sample_from_noteon + i >= 0) {
                frac = modff(note->frequency * (note->sample_from_noteon + i) / env->sample_rate, &intg);
                out[i] += frac < instrument->skew ? -1.0 : 1.0;
            }
        }
    } else {
        note->reached_end = true;
    }
}

void simpleTriangleWaveSynth(SynthEnviormentData* env, SimpleWaveSynthInstrumentData* instrument, SynthNoteData* note, int len, float* out) {
    if(note->sample_from_noteoff < 0) {
        float intg;
        float frac;
        for(int i = 0; i < len; i++) {
            if(note->sample_from_noteon + i >= 0) {
                frac = modff(note->frequency * (note->sample_from_noteon + i) / env->sample_rate, &intg);
                out[i] += (frac < instrument->skew) ? (-1.0 + 2 * frac / instrument->skew) : (-1.0 + 2 * (1 - frac) / (1 - instrument->skew));
            }
        }
    } else {
        note->reached_end = true;
    }
}
