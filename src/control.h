#ifndef _CONTROL_H_
#define _CONTROL_H_

#include "synth-interface.h"

typedef struct {
    SynthInstrumentData* base_instrument_data;
    SynthInstrumentFunction base_instrument_function;
    float volume;
} VolumeControlData;

void volumeControl(SynthEnviormentData* env, VolumeControlData* data, SynthNoteData* note, int len, float* out);

typedef struct {
    SynthInstrumentData* base_instrument_data;
    SynthInstrumentFunction base_instrument_function;
    float frequency;
} FrequencyControlData;

void frequencyControl(SynthEnviormentData* env, FrequencyControlData* data, SynthNoteData* note, int len, float* out);


#endif