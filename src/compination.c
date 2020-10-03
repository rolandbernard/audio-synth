
#include "compination.h"

float multiOctaveEffect(MultiOctaveEffectData* data, SynthNoteData* note) {
    float ret = 0;
    SynthNoteData virt_note = *note;
    bool end = true;
    for(int i = 0; i < data->multiplier_count; i++) {
        virt_note.frequency = note->frequency * data->multipliers[i];
        ret += data->base_instrument_function(data->base_instrument_data, &virt_note);
        if(!virt_note.reached_end) {
            end = false;
        }
    }
    note->reached_end = end;
    return ret;
}

float multiAdditiveInstrument(MultiAdditiveInstrumentData* data, SynthNoteData* note) {
    float ret = 0;
    SynthNoteData virt_note = *note;
    bool end = true;
    for(int i = 0; i < data->instrument_count; i++) {
        ret += data->base_instrument_function[i](data->base_instrument_data[i], &virt_note);
        if(!virt_note.reached_end) {
            end = false;
        }
    }
    note->reached_end = end;
    return ret;
}

float multiDelayEffect(MultiDelayEffectData* data, SynthNoteData* note) {
    float ret = 0;
    SynthNoteData virt_note = *note;
    bool end = true;
    for(int i = 0; i < data->delay_count; i++) {
        virt_note.sample_from_noteon = note->sample_from_noteon - data->sample_rate * data->delays[i];
        virt_note.sample_from_noteoff = note->sample_from_noteoff - data->sample_rate * data->delays[i];
        if(virt_note.sample_from_noteon >= 0) {
            ret += data->base_instrument_function(data->base_instrument_data, &virt_note);
            if(!virt_note.reached_end) {
                end = false;
            }
        }
    }
    note->reached_end = end;
    return ret;
}
