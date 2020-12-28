#ifndef _SYNTH_INTERFACE_H_
#define _SYNTH_INTERFACE_H_

#include <stdbool.h>

typedef struct {
    int sample_rate;
    int* controls;
} SynthEnviormentData;

typedef struct {
} SynthInstrumentData;

typedef struct {
    float frequency;
    float time_from_noteon;
    float time_from_noteoff;
    float sampling_position;
    bool pressed;
    bool released;
    bool reached_end;
    int noteon_velocity;
    int noteoff_velocity;
    int aftertouch;
} SynthNoteData;

typedef float (*SynthInstrumentFunction)(SynthEnviormentData* env, SynthInstrumentData* instrument, SynthNoteData* note);

extern float note_frequencies[128];

#endif