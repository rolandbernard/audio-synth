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
} ModulationSynthData;

float fmSynth(SynthEnviormentData* env, ModulationSynthData* data, SynthNoteData* note);

float amSynth(SynthEnviormentData* env, ModulationSynthData* data, SynthNoteData* note);

#endif