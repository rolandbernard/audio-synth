
#include "compination.h"

float multiOctaveEffect(SynthEnviormentData* env, MultiOctaveEffectData* data, SynthNoteData* note) {
    SynthNoteData virt_note = *note;
    bool end = true;
    float ret = 0;
    for(int i = 0; i < data->multiplier_count; i++) {
        virt_note.frequency = note->frequency * data->multipliers[i];
        ret += data->base_instrument_function(env, data->base_instrument_data, &virt_note);
        if(!virt_note.reached_end) {
            end = false;
        }
    }
    note->reached_end = end;
    return ret;
}

float multiAdditiveInstrument(SynthEnviormentData* env, MultiAdditiveInstrumentData* data, SynthNoteData* note) {
    SynthNoteData virt_note = *note;
    bool end = true;
    float ret = 0;
    for(int i = 0; i < data->instrument_count; i++) {
        ret += data->base_instrument_function[i](env, data->base_instrument_data[i], &virt_note);
        if(!virt_note.reached_end) {
            end = false;
        }
    }
    note->reached_end = end;
    return ret;
}

float multiDelayEffect(SynthEnviormentData* env, MultiDelayEffectData* data, SynthNoteData* note) {
    SynthNoteData virt_note = *note;
    bool end = true;
    float ret = 0;
    for(int i = 0; i < data->delay_count; i++) {
        virt_note.sample_from_noteon = note->sample_from_noteon - env->sample_rate * data->delays[i];
        virt_note.sample_from_noteoff = note->sample_from_noteoff - env->sample_rate * data->delays[i];
        ret += data->base_instrument_function(env, data->base_instrument_data, &virt_note);
        if(!virt_note.reached_end) {
            end = false;
        }
    }
    note->reached_end = end;
    return ret;
}
