#ifndef _OCTAVE_H_
#define _OCTAVE_H_

#include "synth-interface.h"

typedef struct {
    SynthInstrumentData* base_instrument_data;
    SynthInstrumentFunction base_instrument_function;
    int multiplier_count;
    float* multipliers;
} MultiOctaveEffectData;

void multiOctaveEffect(SynthEnviormentData* env, MultiOctaveEffectData* data, SynthNoteData* note, int len, float* out);

typedef struct {
    int instrument_count;
    SynthInstrumentData** base_instrument_data;
    SynthInstrumentFunction* base_instrument_function;
} MultiAdditiveInstrumentData;

void multiAdditiveInstrument(SynthEnviormentData* env, MultiAdditiveInstrumentData* data, SynthNoteData* note, int len, float* out);

typedef struct {
    SynthInstrumentData* base_instrument_data;
    SynthInstrumentFunction base_instrument_function;
    int delay_count;
    float* delays;
} MultiDelayEffectData;

void multiDelayEffect(SynthEnviormentData* env, MultiDelayEffectData* data, SynthNoteData* note, int len, float* out);

#endif