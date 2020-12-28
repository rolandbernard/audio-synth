
#include "modulate.h"

float fmSynth(SynthEnviormentData* env, ModulationSynthData* data, SynthNoteData* note) {
    float old_freq = note->frequency;
    note->frequency *= data->modulator_function(env, data->modulator_data, note) * data->amplitude + data->base;
    note->reached_end = false;
    float ret = data->carrier_function(env, data->carrier_data, note);
    note->frequency = old_freq;
    return ret;
}

float amSynth(SynthEnviormentData* env, ModulationSynthData* data, SynthNoteData* note) {
    float scale = data->modulator_function(env, data->modulator_data, note) * data->amplitude + data->base;
    note->reached_end = false;
    return scale * data->carrier_function(env, data->carrier_data, note);
}
