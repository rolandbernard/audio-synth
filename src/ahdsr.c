
#include <stdio.h>

#include "ahdsr.h"

void ahdsrEnvelope(SynthEnviormentData* env, AhdsrEnvelopeData* data, SynthNoteData* note, int len, float* out) {
    if(note->reached_end) {
        return;
    } else {
        float tmp_out[len];
        for(int i = 0; i < len; i++) {
            tmp_out[i] = 0;
        }
        data->base_instrument_function(env, data->base_instrument_data, note, len, tmp_out);
        for(int i = 0; i < len && !note->reached_end; i++) {
            float scale = 0;
            float time = (float)(note->sample_from_noteon + i) / (float)env->sample_rate;
            if (time < data->delay) {
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
                if (data->release == 0.0) {
                    note->reached_end = true;
                    scale = 0;
                } else {
                    float time = (float)(note->sample_from_noteoff + i) / (float)env->sample_rate;
                    if (time > data->release) {
                        note->reached_end = true;
                        scale = 0;
                    } else {
                        scale *= 1.0 - (time / data->release);
                    }
                }
            }
            out[i] += tmp_out[i] * scale;
        }
    }
}
