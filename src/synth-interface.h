#ifndef _SYNTH_INTERFACE_H_
#define _SYNTH_INTERFACE_H_

#include <stdbool.h>

#define SYNTH_INSTRUMENT_DATA_BASE int sample_rate; 

typedef struct {
    SYNTH_INSTRUMENT_DATA_BASE
} SynthInstrumentData;

typedef struct {
    float frequency;
    long sample_from_noteon;
    long sample_from_noteoff;
    bool reached_end;
} SynthNoteData;

typedef float (*SynthInstrumentFunction)(SynthInstrumentData* instrument, SynthNoteData* note);

extern float note_frequencies[128];

#endif