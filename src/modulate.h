#ifndef _FM_H_
#define _FM_H_

#include "synth-interface.h"

typedef struct {
    SynthInstrumentData* carrier_data;
    SynthInstrumentFunction carrier_function;
    SynthInstrumentData* modulator_data;
    SynthInstrumentFunction modulator_function;
    float base;
    float amplitude;
} FmSynthData;

float fmSynth(SynthEnviormentData* env, FmSynthData* data, SynthNoteData* note);

typedef struct {
    SynthInstrumentData* carrier_data;
    SynthInstrumentFunction carrier_function;
    SynthInstrumentData* modulator_data;
    SynthInstrumentFunction modulator_function;
    float base;
    float amplitude;
} AmSynthData;

float amSynth(SynthEnviormentData* env, AmSynthData* data, SynthNoteData* note);

#endif