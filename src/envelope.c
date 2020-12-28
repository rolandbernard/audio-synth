
#include <stdio.h>

#include "envelope.h"

float ahdsrEnvelope(SynthEnviormentData* env, AhdsrEnvelopeData* data, SynthNoteData* note) {
    if (!note->reached_end) {
        float scale = 0.0;
        float time = note->time_from_noteon;
        if (time < data->delay) {
            return 0.0;
        } else if (time - data->delay < data->attack) {
            scale = (time - data->delay) / data->attack;
        } else if (time - data->delay - data->attack < data->hold) {
            scale = 1.0;
        } else if (time - data->delay - data->attack - data->hold < data->decay) {
            scale = (1.0 - ((time - data->delay - data->attack - data->hold) / data->decay)) * (1.0 - data->sustain) + data->sustain;
        } else {
            if (data->sustain == 0.0) {
                note->reached_end = true;
                return 0.0;
            } else {
                scale = data->sustain;
            }
        }
        if (note->released) {
            if (data->release == 0.0) {
                note->reached_end = true;
                return 0.0;
            } else {
                float time = note->time_from_noteoff;
                if (time > data->release) {
                    note->reached_end = true;
                    return 0.0;
                } else {
                    scale *= 1.0 - (time / data->release);
                }
            }
        }
        return scale * data->base_instrument_function(env, data->base_instrument_data, note);
    }
    return 0.0;
}

float simpleEnvelope(SynthEnviormentData* env, SimpleEnvelopeData* data, SynthNoteData* note) {
    if(!note->released && !note->reached_end) {
        return data->base_instrument_function(env, data->base_instrument_data, note);
    } else {
        note->reached_end = true;
        return 0.0;
    }
}
