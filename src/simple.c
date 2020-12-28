
#include <math.h>
#include "simple.h"

#define PI 3.14159265358979323846

float simpleSineWaveSynth(SynthEnviormentData* env, SynthInstrumentData* instrument, SynthNoteData* note) {
    note->sampling_position += 2 * PI * note->frequency / env->sample_rate;
    return sinf(note->sampling_position);
}

float simpleSquareWaveSynth(SynthEnviormentData* env, SimpleWaveSynthInstrumentData* instrument, SynthNoteData* note) {
    float intg;
    float frac;
    note->sampling_position += 2 * PI * note->frequency / env->sample_rate;
    frac = modff(note->sampling_position, &intg);
    return frac < instrument->skew ? -1.0 : 1.0;
}

float simpleTriangleWaveSynth(SynthEnviormentData* env, SimpleWaveSynthInstrumentData* instrument, SynthNoteData* note) {
    float intg;
    float frac;
    note->sampling_position += 2 * PI * note->frequency / env->sample_rate;
    frac = modff(note->sampling_position, &intg);
    return (frac < instrument->skew) ? (-1.0 + 2 * frac / instrument->skew) : (-1.0 + 2 * (1 - frac) / (1 - instrument->skew));
}

float simpleTimedSineWaveSynth(SynthEnviormentData* env, SynthInstrumentData* instrument, SynthNoteData* note) {
    return sinf(note->time_from_noteon * 2 * PI * note->frequency);
}

float simpleTimedSquareWaveSynth(SynthEnviormentData* env, SimpleWaveSynthInstrumentData* instrument, SynthNoteData* note) {
    float intg;
    float frac;
    frac = modff(note->time_from_noteon * 2 * PI * note->frequency, &intg);
    return frac < instrument->skew ? -1.0 : 1.0;
}

float simpleTimedTriangleWaveSynth(SynthEnviormentData* env, SimpleWaveSynthInstrumentData* instrument, SynthNoteData* note) {
    float intg;
    float frac;
    frac = modff(note->time_from_noteon * 2 * PI * note->frequency, &intg);
    return (frac < instrument->skew) ? (-1.0 + 2 * frac / instrument->skew) : (-1.0 + 2 * (1 - frac) / (1 - instrument->skew));
}

float constantValue(SynthEnviormentData* env, ConstantInstrumentData* instrument, SynthNoteData* note) {
    return instrument->value;
}
