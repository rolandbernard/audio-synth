
#include "compination.h"

void multiOctaveEffect(SynthEnviormentData* env, MultiOctaveEffectData* data, SynthNoteData* note, int len, float* out) {
    SynthNoteData virt_note = *note;
    bool end = true;
    for(int i = 0; i < data->multiplier_count; i++) {
        virt_note.frequency = note->frequency * data->multipliers[i];
        data->base_instrument_function(env, data->base_instrument_data, &virt_note, len, out);
        if(!virt_note.reached_end) {
            end = false;
        }
    }
    note->reached_end = end;
}

void multiAdditiveInstrument(SynthEnviormentData* env, MultiAdditiveInstrumentData* data, SynthNoteData* note, int len, float* out) {
    SynthNoteData virt_note = *note;
    bool end = true;
    for(int i = 0; i < data->instrument_count; i++) {
        data->base_instrument_function[i](env, data->base_instrument_data[i], &virt_note, len, out);
        if(!virt_note.reached_end) {
            end = false;
        }
    }
    note->reached_end = end;
}

void multiDelayEffect(SynthEnviormentData* env, MultiDelayEffectData* data, SynthNoteData* note, int len, float* out) {
    SynthNoteData virt_note = *note;
    bool end = true;
    for(int i = 0; i < data->delay_count; i++) {
        virt_note.sample_from_noteon = note->sample_from_noteon - env->sample_rate * data->delays[i];
        virt_note.sample_from_noteoff = note->sample_from_noteoff - env->sample_rate * data->delays[i];
        data->base_instrument_function(env, data->base_instrument_data, &virt_note, len, out);
        if(!virt_note.reached_end) {
            end = false;
        }
    }
    note->reached_end = end;
}
