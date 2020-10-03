
#include <stdio.h>

#include "ahdsr.h"

float ahdsrEnvelope(AhdsrEnvelopeData* data, SynthNoteData* note) {
    if(note->reached_end) {
        return 0.0;
    } else {
        float scale = 0;
        float time = (float)note->sample_from_noteon / (float)data->sample_rate;
        if(time < data->delay) {
            scale = 0.0;
        } else if (time - data->delay < data->attack) {
            scale = (time - data->delay) / data->attack;
        } else if (time - data->delay - data->attack < data->hold) {
            scale = 1.0;
        } else if (time - data->delay - data->attack - data->hold < data->decay) {
            scale = (1.0 - ((time - data->delay - data->attack - data->hold) / data->decay)) * (1.0 - data->sustain) + data->sustain;
        } else {
            if (data->sustain == 0.0) {
                note->reached_end = true;
                scale = 0.0;
            } else {
                scale = data->sustain;
            }
        }
        if (note->sample_from_noteoff >= 0) {
            if(data->release == 0.0) {
                note->reached_end = true;
                scale = 0;
            } else {
                float time = (float)note->sample_from_noteoff / (float)data->sample_rate;
                if (time > data->release) {
                    note->reached_end = true;
                    scale = 0;
                } else {
                    scale *= 1.0 - (time / data->release);
                }
            }
        }
        return scale * data->base_instrument_function(data->base_instrument_data, note);
    }
}
