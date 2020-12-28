#ifndef _SIMPLE_H_
#define _SIMPLE_H_

#include "synth-interface.h"

typedef struct {
    float skew;
} SimpleWaveSynthInstrumentData;

float simpleSineWaveSynth(SynthEnviormentData* env, SynthInstrumentData* instrument, SynthNoteData* note);

float simpleSquareWaveSynth(SynthEnviormentData* env, SimpleWaveSynthInstrumentData* instrument, SynthNoteData* note);

float simpleTriangleWaveSynth(SynthEnviormentData* env, SimpleWaveSynthInstrumentData* instrument, SynthNoteData* note);

float simpleTimedSineWaveSynth(SynthEnviormentData* env, SynthInstrumentData* instrument, SynthNoteData* note);

float simpleTimedSquareWaveSynth(SynthEnviormentData* env, SimpleWaveSynthInstrumentData* instrument, SynthNoteData* note);

float simpleTimedTriangleWaveSynth(SynthEnviormentData* env, SimpleWaveSynthInstrumentData* instrument, SynthNoteData* note);

typedef struct {
    float value;
} ConstantInstrumentData;

float constantValue(SynthEnviormentData* env, ConstantInstrumentData* instrument, SynthNoteData* note);

#endif