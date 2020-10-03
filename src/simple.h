#ifndef _SIMPLE_H_
#define _SIMPLE_H_

#include "synth-interface.h"

typedef struct {
    SYNTH_INSTRUMENT_DATA_BASE
    float skew;
} SimpleWaveSynthInstrumentData;

float simpleSineWaveSynth(SimpleWaveSynthInstrumentData* instrument, SynthNoteData* note);

float simpleSquareWaveSynth(SimpleWaveSynthInstrumentData* instrument, SynthNoteData* note);

float simpleTriangleWaveSynth(SimpleWaveSynthInstrumentData* instrument, SynthNoteData* note);

#endif