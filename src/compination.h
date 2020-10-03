#ifndef _OCTAVE_H_
#define _OCTAVE_H_

#include "synth-interface.h"

typedef struct {
    SYNTH_INSTRUMENT_DATA_BASE
    SynthInstrumentData* base_instrument_data;
    SynthInstrumentFunction base_instrument_function;
    int multiplier_count;
    float* multipliers;
} MultiOctaveEffectData;

float multiOctaveEffect(MultiOctaveEffectData* data, SynthNoteData* note);

typedef struct {
    SYNTH_INSTRUMENT_DATA_BASE
    int instrument_count;
    SynthInstrumentData** base_instrument_data;
    SynthInstrumentFunction* base_instrument_function;
} MultiAdditiveInstrumentData;

float multiAdditiveInstrument(MultiAdditiveInstrumentData* data, SynthNoteData* note);

typedef struct {
    SYNTH_INSTRUMENT_DATA_BASE
    SynthInstrumentData* base_instrument_data;
    SynthInstrumentFunction base_instrument_function;
    int delay_count;
    float* delays;
} MultiDelayEffectData;

float multiDelayEffect(MultiDelayEffectData* data, SynthNoteData* note);

#endif