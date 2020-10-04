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
    long sample_from_noteon;
    int noteon_velocity;
    int aftertouch;
    long sample_from_noteoff;
    int noteoff_velocity;
    bool reached_end;
} SynthNoteData;

typedef void (*SynthInstrumentFunction)(SynthEnviormentData* env, SynthInstrumentData* instrument, SynthNoteData* note, int len, float* out);

extern float note_frequencies[128];

#endif