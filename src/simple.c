
#include <math.h>
#include "simple.h"

#define PI 3.14159265358979323846

float simpleSineWaveSynth(SimpleWaveSynthInstrumentData* instrument, SynthNoteData* note) {
    return sinf(2 * PI * note->frequency * note->sample_from_noteon / instrument->sample_rate);
}

float simpleSquareWaveSynth(SimpleWaveSynthInstrumentData* instrument, SynthNoteData* note) {
    float intg;
    float frac = modff(note->frequency * note->sample_from_noteon / instrument->sample_rate, &intg);
    return frac < instrument->skew ? -1.0 : 1.0;
}

float simpleTriangleWaveSynth(SimpleWaveSynthInstrumentData* instrument, SynthNoteData* note) {
    float intg;
    float frac = modff(note->frequency * note->sample_from_noteon / instrument->sample_rate, &intg);
    return (frac < instrument->skew) ? (-1.0 + 2 * frac / instrument->skew) : (-1.0 + 2 * (1 - frac) / (1 - instrument->skew));
}
