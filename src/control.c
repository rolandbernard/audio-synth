
#include "control.h"

float volumeControl(SynthEnviormentData* env, VolumeControlData* data, SynthNoteData* note) {
    return data->base_instrument_function(env, data->base_instrument_data, note) * data->volume;
}

float frequencyControl(SynthEnviormentData* env, FrequencyControlData* data, SynthNoteData* note) {
    SynthNoteData virt_note = *note;
    virt_note.frequency *= data->frequency;
    float ret = data->base_instrument_function(env, data->base_instrument_data, &virt_note);
    if(virt_note.reached_end) {
        note->reached_end = true;
    }
    return ret;
}

float constFrequencyControl(SynthEnviormentData* env, ConstFrequencyControlData* data, SynthNoteData* note) {
    SynthNoteData virt_note = *note;
    virt_note.frequency = data->frequency;
    float ret = data->base_instrument_function(env, data->base_instrument_data, &virt_note);
    if(virt_note.reached_end) {
        note->reached_end = true;
    }
    return ret;
}
