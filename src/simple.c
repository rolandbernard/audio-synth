
#include <math.h>
#include "simple.h"

#define PI 3.14159265358979323846

float simpleSineWaveSynth(SynthEnviormentData* env, SynthInstrumentData* instrument, SynthNoteData* note) {
    if(note->sample_from_noteoff < 0) {
        if(note->sample_from_noteon >= 0) {
            return sinf(2 * PI * note->frequency * note->sample_from_noteon / env->sample_rate);
        }
    } else {
        note->reached_end = true;
    }
    return 0.0;
}

float simpleSquareWaveSynth(SynthEnviormentData* env, SimpleWaveSynthInstrumentData* instrument, SynthNoteData* note) {
    if(note->sample_from_noteoff < 0) {
        float intg;
        float frac;
        if(note->sample_from_noteon >= 0) {
            frac = modff(note->frequency * note->sample_from_noteon / env->sample_rate, &intg);
            return frac < instrument->skew ? -1.0 : 1.0;
        }
    } else {
        note->reached_end = true;
    }
    return 0.0;
}

float simpleTriangleWaveSynth(SynthEnviormentData* env, SimpleWaveSynthInstrumentData* instrument, SynthNoteData* note) {
    if(note->sample_from_noteoff < 0) {
        float intg;
        float frac;
        if(note->sample_from_noteon >= 0) {
            frac = modff(note->frequency * note->sample_from_noteon / env->sample_rate, &intg);
            return (frac < instrument->skew) ? (-1.0 + 2 * frac / instrument->skew) : (-1.0 + 2 * (1 - frac) / (1 - instrument->skew));
        }
    } else {
        note->reached_end = true;
    }
    return 0.0;
}

float constantValue(SynthEnviormentData* env, ConstantInstrumentData* instrument, SynthNoteData* note) {
    return instrument->value;
}
