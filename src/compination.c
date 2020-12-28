
#include "compination.h"

float multiOctaveEffect(SynthEnviormentData* env, MultiOctaveEffectData* data, SynthNoteData* note) {
    bool end = true;
    float ret = 0;
    float old_freq = note->frequency;
    float old_sample_pos = note->sampling_position;
    for(int i = 0; i < data->multiplier_count; i++) {
        note->frequency = old_freq * data->multipliers[i];
        note->sampling_position = old_sample_pos * data->multipliers[i];
        ret += data->base_instrument_function(env, data->base_instrument_data, note);
        if(!note->reached_end) {
            end = false;
        }
    }
    note->sampling_position /= data->multipliers[data->multiplier_count - 1];
    note->frequency = old_freq;
    note->reached_end = end;
    return ret;
}

float multiAdditiveInstrument(SynthEnviormentData* env, MultiAdditiveInstrumentData* data, SynthNoteData* note) {
    bool end = true;
    float ret = 0;
    float old_sample_pos = note->sampling_position;
    for(int i = 0; i < data->instrument_count; i++) {
        note->sampling_position = old_sample_pos;
        ret += data->base_instrument_function[i](env, data->base_instrument_data[i], note);
        if(!note->reached_end) {
            end = false;
        }
    }
    note->reached_end = end;
    return ret;
}

float multiDelayEffect(SynthEnviormentData* env, MultiDelayEffectData* data, SynthNoteData* note) {
    bool end = true;
    float ret = 0.0;
    float old_from_on = note->time_from_noteon;
    float old_from_off = note->time_from_noteoff;
    bool old_released = note->released;
    float old_sample_pos = note->sampling_position;
    for(int i = 0; i < data->delay_count; i++) {
        note->released = old_released;
        note->time_from_noteon = old_from_on - data->delays[i];
        if (note->time_from_noteon >= 0.0) {   
            note->time_from_noteoff = old_from_off -  data->delays[i];
            note->sampling_position = old_sample_pos;
            if (note->time_from_noteoff < 0) {
                note->released = false;
            }
            ret += data->base_instrument_function(env, data->base_instrument_data, note);
        }
        if(note->reached_end) {
            note->reached_end = false;
        } else {
            end = false;
        }
    }
    note->time_from_noteon = old_from_on;
    note->time_from_noteoff = old_from_off;
    note->released = old_released;
    note->reached_end = end;
    return ret;
}
