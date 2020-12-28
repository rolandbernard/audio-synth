#ifndef _AHDSR_H_
#define _AHDSR_H_

#include "synth-interface.h"

typedef struct {
    SynthInstrumentData* base_instrument_data;
    SynthInstrumentFunction base_instrument_function;
    float delay;
    float attack;
    float hold;
    float decay;
    float sustain;
    float release;
} AhdsrEnvelopeData;

float ahdsrEnvelope(SynthEnviormentData* env, AhdsrEnvelopeData* data, SynthNoteData* note);

#endif