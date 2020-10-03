#ifndef _AHDSR_H_
#define _AHDSR_H_

#include "synth-interface.h"

typedef struct {
    SYNTH_INSTRUMENT_DATA_BASE
    SynthInstrumentData* base_instrument_data;
    SynthInstrumentFunction base_instrument_function;
    float attack;
    float hold;
    float decay;
    float sustain;
    float release;
} AhdsrEnvelopeData;

float ahdsrEnvelope(AhdsrEnvelopeData* data, SynthNoteData* note);

#endif