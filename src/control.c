
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

float controlIntValue(SynthEnviormentData* env, ControlIntValueData* data, SynthNoteData* note) {
    *(data->write_to) = env->controls[data->control_number] * data->multiply / data->divide + data->offset;
    return data->base_instrument_function(env, data->base_instrument_data, note);
}

float controlFloatValue(SynthEnviormentData* env, ControlFloatValueData* data, SynthNoteData* note) {
    *(data->write_to) = env->controls[data->control_number] * data->multiply + data->offset;
    return data->base_instrument_function(env, data->base_instrument_data, note);
}

float velocityOnIntValue(SynthEnviormentData* env, VelocityIntValueData* data, SynthNoteData* note) {
    *(data->write_to) = note->noteon_velocity * data->multiply / data->divide + data->offset;
    return data->base_instrument_function(env, data->base_instrument_data, note);
}

float velocityOffIntValue(SynthEnviormentData* env, VelocityIntValueData* data, SynthNoteData* note) {
    *(data->write_to) = note->noteoff_velocity * data->multiply / data->divide + data->offset;
    return data->base_instrument_function(env, data->base_instrument_data, note);
}

float aftertouchIntValue(SynthEnviormentData* env, VelocityIntValueData* data, SynthNoteData* note) {
    *(data->write_to) = note->aftertouch * data->multiply / data->divide + data->offset;
    return data->base_instrument_function(env, data->base_instrument_data, note);
}

float velocityOnFloatValue(SynthEnviormentData* env, VelocityFloatValueData* data, SynthNoteData* note) {
    *(data->write_to) = note->noteon_velocity * data->multiply + data->offset;
    return data->base_instrument_function(env, data->base_instrument_data, note);
}

float velocityOffFloatValue(SynthEnviormentData* env, VelocityFloatValueData* data, SynthNoteData* note) {
    *(data->write_to) = note->noteoff_velocity * data->multiply + data->offset;
    return data->base_instrument_function(env, data->base_instrument_data, note);
}

float aftertouchFloatValue(SynthEnviormentData* env, VelocityFloatValueData* data, SynthNoteData* note) {
    *(data->write_to) = note->aftertouch * data->multiply + data->offset;
    return data->base_instrument_function(env, data->base_instrument_data, note);
}
