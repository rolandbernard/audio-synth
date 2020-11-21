
#include "control.h"

void volumeControl(SynthEnviormentData* env, VolumeControlData* data, SynthNoteData* note, int len, float* out) {
    data->base_instrument_function(env, data->base_instrument_data, note, len, out);
    for(int i = 0; i < len; i++) {
        out[i] *= data->volume;
    }
}

void frequencyControl(SynthEnviormentData* env, FrequencyControlData* data, SynthNoteData* note, int len, float* out) {
    SynthNoteData virt_note = *note;
    virt_note.frequency *= data->frequency;
    data->base_instrument_function(env, data->base_instrument_data, note, len, out);
    if(virt_note.reached_end) {
        note->reached_end = true;
    }
}

