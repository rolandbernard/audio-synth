#ifndef _SIMPLE_H_
#define _SIMPLE_H_

#include "synth-interface.h"

typedef struct {
    float skew;
} SimpleWaveSynthInstrumentData;

void simpleSineWaveSynth(SynthEnviormentData* env, SynthInstrumentData* instrument, SynthNoteData* note, int len, float* out);

void simpleSquareWaveSynth(SynthEnviormentData* env, SimpleWaveSynthInstrumentData* instrument, SynthNoteData* note, int len, float* out);

void simpleTriangleWaveSynth(SynthEnviormentData* env, SimpleWaveSynthInstrumentData* instrument, SynthNoteData* note, int len, float* out);

#endif