
#include "control.h"

float volumeControl(SynthEnviormentData* env, VolumeControlData* data, SynthNoteData* note) {
    return data->base_instrument_function(env, data->base_instrument_data, note) * data->volume;
}

float frequencyControl(SynthEnviormentData* env, FrequencyControlData* data, SynthNoteData* note) {
    float old_freq = note->frequency;
    note->frequency *= data->frequency;
    float ret = data->base_instrument_function(env, data->base_instrument_data, note);
    note->frequency = old_freq;
    return ret;
}

float constFrequencyControl(SynthEnviormentData* env, ConstFrequencyControlData* data, SynthNoteData* note) {
    float old_freq = note->frequency;
    note->frequency = data->frequency;
    float ret = data->base_instrument_function(env, data->base_instrument_data, note);
    note->frequency = old_freq;
    return ret;
}
