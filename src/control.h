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

typedef struct {
    SynthInstrumentData* base_instrument_data;
    SynthInstrumentFunction base_instrument_function;
    int control_number;
    int* write_to;
    int offset;
    int multiply;
    int divide;
} ControlIntValueData;

float controlIntValue(SynthEnviormentData* env, ControlIntValueData* data, SynthNoteData* note);

typedef struct {
    SynthInstrumentData* base_instrument_data;
    SynthInstrumentFunction base_instrument_function;
    int control_number;
    float* write_to;
    float offset;
    float multiply;
} ControlFloatValueData;

float controlFloatValue(SynthEnviormentData* env, ControlFloatValueData* data, SynthNoteData* note);

typedef struct {
    SynthInstrumentData* base_instrument_data;
    SynthInstrumentFunction base_instrument_function;
    int* write_to;
    int offset;
    int multiply;
    int divide;
} VelocityIntValueData;

float velocityOnIntValue(SynthEnviormentData* env, VelocityIntValueData* data, SynthNoteData* note);

float velocityOffIntValue(SynthEnviormentData* env, VelocityIntValueData* data, SynthNoteData* note);

float aftertouchIntValue(SynthEnviormentData* env, VelocityIntValueData* data, SynthNoteData* note);

typedef struct {
    SynthInstrumentData* base_instrument_data;
    SynthInstrumentFunction base_instrument_function;
    float* write_to;
    float offset;
    float multiply;
} VelocityFloatValueData;

float velocityOnFloatValue(SynthEnviormentData* env, VelocityFloatValueData* data, SynthNoteData* note);

float velocityOffFloatValue(SynthEnviormentData* env, VelocityFloatValueData* data, SynthNoteData* note);

float aftertouchFloatValue(SynthEnviormentData* env, VelocityFloatValueData* data, SynthNoteData* note);

#endif