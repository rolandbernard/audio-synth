#ifndef _OCTAVE_H_
#define _OCTAVE_H_

#include "synth-interface.h"

typedef struct {
    SynthInstrumentData* base_instrument_data;
    SynthInstrumentFunction base_instrument_function;
    int multiplier_count;
    float* multipliers;
} MultiOctaveEffectData;

float multiOctaveEffect(SynthEnviormentData* env, MultiOctaveEffectData* data, SynthNoteData* note);

typedef struct {
    int instrument_count;
    SynthInstrumentData** base_instrument_data;
    SynthInstrumentFunction* base_instrument_function;
} MultiAdditiveInstrumentData;

float multiAdditiveInstrument(SynthEnviormentData* env, MultiAdditiveInstrumentData* data, SynthNoteData* note);

typedef struct {
    SynthInstrumentData* base_instrument_data;
    SynthInstrumentFunction base_instrument_function;
    int delay_count;
    float* delays;
} MultiDelayEffectData;

float multiDelayEffect(SynthEnviormentData* env, MultiDelayEffectData* data, SynthNoteData* note);

#endif