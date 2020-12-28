
#include "modulate.h"

float fmSynth(SynthEnviormentData* env, FmSynthData* data, SynthNoteData* note) {
    SynthNoteData virt_note = *note;
    virt_note.frequency *= data->modulator_function(env, data->modulator_data, note) * data->amplitude + data->base;
    float ret = data->carrier_function(env, data->carrier_data, &virt_note);
    if(virt_note.reached_end) {
        note->reached_end = true;
    }
    return ret;
}

float amSynth(SynthEnviormentData* env, AmSynthData* data, SynthNoteData* note) {
    float scale = data->modulator_function(env, data->modulator_data, note) * data->amplitude + data->base;
    return data->carrier_function(env, data->carrier_data, note) * scale;
}
