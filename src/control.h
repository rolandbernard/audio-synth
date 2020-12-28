#ifndef _CONTROL_H_
#define _CONTROL_H_

#include "synth-interface.h"

typedef struct {
    SynthInstrumentData* base_instrument_data;
    SynthInstrumentFunction base_instrument_function;
    float volume;
} VolumeControlData;

float volumeControl(SynthEnviormentData* env, VolumeControlData* data, SynthNoteData* note);

typedef struct {
    SynthInstrumentData* base_instrument_data;
    SynthInstrumentFunction base_instrument_function;
    float frequency;
} FrequencyControlData;

float frequencyControl(SynthEnviormentData* env, FrequencyControlData* data, SynthNoteData* note);

typedef struct {
    SynthInstrumentData* base_instrument_data;
    SynthInstrumentFunction base_instrument_function;
    float frequency;
} ConstFrequencyControlData;

float constFrequencyControl(SynthEnviormentData* env, ConstFrequencyControlData* data, SynthNoteData* note);

#endif