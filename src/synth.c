
#include <portmidi.h>
#include <portaudio.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <math.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

#include "simple.h"
#include "compination.h"
#include "envelope.h"
#include "control.h"
#include "modulate.h"

#define SAMPLE_RATE 44100
#define CHANNELS 2
#define BIT_SIZE 16
#define POLYPHONY 500

int controls[16][128];
SynthEnviormentData env = {
    .sample_rate = SAMPLE_RATE,
};
SimpleWaveSynthInstrumentData params = { 0.1 };
ConstantInstrumentData const_data = { 1.0 };
AhdsrEnvelopeData freq_env = {
    .base_instrument_data = (SynthInstrumentData*)&const_data,
    .base_instrument_function = (SynthInstrumentFunction)constantValue,
    .delay = 0.0,
    .attack = 0.0,
    .hold = 0.0,
    .decay = 0.0,
    .sustain = 1.0,
    .release = 0.5,
};
// SynthInstrumentData* data[] = { (SynthInstrumentData*)&params, (SynthInstrumentData*)&params, (SynthInstrumentData*)&params };
// SynthInstrumentFunction funcs[] = { (SynthInstrumentFunction)simpleSineWaveSynth, (SynthInstrumentFunction)simpleSquareWaveSynth, (SynthInstrumentFunction)simpleTriangleWaveSynth };
SynthInstrumentData* data[] = { (SynthInstrumentData*)&params };
SynthInstrumentFunction funcs[] = { (SynthInstrumentFunction)simpleSineWaveSynth };
MultiAdditiveInstrumentData additiv = {
    .instrument_count = sizeof(data)/sizeof(data[0]),
    .base_instrument_data = (SynthInstrumentData**)&data,
    .base_instrument_function = (SynthInstrumentFunction*)&funcs,
};
ModulationSynthData am_data = {
    .carrier_data = (SynthInstrumentData*)&additiv,
    .carrier_function = (SynthInstrumentFunction)multiAdditiveInstrument,
    .modulator_data = (SynthInstrumentData*)&freq_env,
    .modulator_function = (SynthInstrumentFunction)ahdsrEnvelope,
    .base = 1,
    .amplitude = 0.01,
};
float octave_mults[] = { 0.125, 0.25, 0.5, 1, 2, 4, 8 };
// float octave_mults[] = { 1 };
MultiOctaveEffectData octave = {
    .base_instrument_data = (SynthInstrumentData*)&am_data,
    .base_instrument_function = (SynthInstrumentFunction)fmSynth,
    .multiplier_count = sizeof(octave_mults) / sizeof(octave_mults[0]),
    .multipliers = octave_mults,
};
VolumeControlData volume_vel = {
    .base_instrument_data = (SynthInstrumentData*)&octave,
    .base_instrument_function = (SynthInstrumentFunction)multiOctaveEffect,
    .volume = 1.0,
    // .volume = 0.05,
};
VelocityFloatValueData vel_vol_contr = {
    .base_instrument_data = (SynthInstrumentData*)&volume_vel,
    .base_instrument_function = (SynthInstrumentFunction)volumeControl,
    .write_to = &volume_vel.volume,
    .offset = 0,
    .multiply = 1.0 / 127.0,
};
VolumeControlData volume_main = {
    .base_instrument_data = (SynthInstrumentData*)&vel_vol_contr,
    .base_instrument_function = (SynthInstrumentFunction)velocityOnFloatValue,
    .volume = 0.01,
    // .volume = 0.05,
};
ControlFloatValueData vol_contr = {
    .base_instrument_data = (SynthInstrumentData*)&volume_main,
    .base_instrument_function = (SynthInstrumentFunction)volumeControl,
    .control_number = 7,
    .write_to = &volume_main.volume,
    .offset = 0,
    .multiply = 1 / 127.0,
};
AhdsrEnvelopeData envelope = {
    .base_instrument_data = (SynthInstrumentData*)&vol_contr,
    .base_instrument_function = (SynthInstrumentFunction)controlFloatValue,
    .delay = 0.0,
    .attack = 0.1,
    .hold = 0.0,
    .decay = 0.75,
    .sustain = 0.2,
    .release = 0.5,
};
VelocityFloatValueData vel_atk_contr = {
    .base_instrument_data = (SynthInstrumentData*)&envelope,
    .base_instrument_function = (SynthInstrumentFunction)ahdsrEnvelope,
    .write_to = &envelope.attack,
    .offset = 0.25,
    .multiply = -0.25 / 127.0,
};
VelocityFloatValueData vel_rls_contr = {
    .base_instrument_data = (SynthInstrumentData*)&vel_atk_contr,
    .base_instrument_function = (SynthInstrumentFunction)velocityOnFloatValue,
    .write_to = &envelope.attack,
    .offset = 0.25,
    .multiply = -0.25 / 127.0,
};
VolumeControlData volume_final = {
    .base_instrument_data = (SynthInstrumentData*)&vel_rls_contr,
    .base_instrument_function = (SynthInstrumentFunction)velocityOffFloatValue,
    .volume = 0.01,
    // .volume = 0.05,
};
int sample = 0;

SynthInstrumentData* instrument_data = (SynthInstrumentData*)&volume_final;
SynthInstrumentFunction instrument_function = (SynthInstrumentFunction)volumeControl;

int num_notes = 0;
SynthNoteData notes[POLYPHONY];
int note_channel[POLYPHONY];
int note_to_last_notes[128];

int audioCallback(const void* input, void* output, uint64_t frame_count, const PaStreamCallbackTimeInfo* time_info, PaStreamCallbackFlags status_flage, void* user_data) {
    float (*out)[CHANNELS] = (float(*)[CHANNELS])output;
    for(int i = 0; i < frame_count; i++) {
        for(int c = 0; c < CHANNELS; c++) {
            out[i][c] = 0;
        }
    }
    for(int i = 0; i < POLYPHONY; i++) {
        if(notes[i].pressed) {
            env.controls = controls[note_channel[i]];
            for(int j = 0; !notes[i].reached_end && j < frame_count; j++) {
                float val = instrument_function(&env, instrument_data, &notes[i]);
                notes[i].time_from_noteon += 1.0 / env.sample_rate;
                if (notes[i].released) {
                    notes[i].time_from_noteoff += 1.0 / env.sample_rate;
                }
                for (int c = 0; c < CHANNELS; c++) {
                    out[j][c] += val;
                }
            }
        }
    }
    return 0;
}

int main(int argc, char** argv) {
    for(int i = 0; i < 16; i++) {
        controls[i][7] = 100;
    }
    for(int i = 0; i < POLYPHONY; i++) {
        notes[i].time_from_noteoff = 0;
        notes[i].time_from_noteon = 0;
        notes[i].sampling_position = 0;
        notes[i].pressed = false;
        notes[i].released = false;
        notes[i].reached_end = true;
    }
    for(int i = 0; i < 128; i++) {
        note_to_last_notes[i] = -1;
    }
    
    Pm_Initialize();
    PortMidiStream* midi_stream;
    int device_count = Pm_CountDevices();
    for(int i = 0; i < device_count; i++) {
        const PmDeviceInfo* device = Pm_GetDeviceInfo(i);
        fprintf(stderr, "%i: %s\n", i, device->name);
    }
    fprintf(stderr, "Select id: ");
    fflush(stderr);
    int id;
    fscanf(stdin, "%i", &id);
    PmError err = Pm_OpenInput(&midi_stream, id, NULL, 64, NULL, NULL);
    if(err) {   
        fprintf(stderr, "err: %s\n", Pm_GetErrorText(err));
        return EXIT_FAILURE;
    }

    PaStream* audio_stream;
    freopen("/dev/null","w",stderr);
    Pa_Initialize(); 
    freopen("/dev/tty","w",stderr);
    Pa_OpenDefaultStream(&audio_stream, 0, CHANNELS, paFloat32, SAMPLE_RATE, paFramesPerBufferUnspecified, audioCallback, NULL);
    Pa_StartStream(audio_stream);

    for(;;) {
        PmError poll = Pm_Poll(midi_stream);
        if(poll > 0) {
            PmEvent buffer[64];
            int len = Pm_Read(midi_stream, buffer, 64);
            if(len > 0) {
                for (int i = 0; i < len; i++) {
                    if ((Pm_MessageStatus(buffer[i].message) & 0xf0) == 0x90) {
                        int note_num = Pm_MessageData1(buffer[i].message);
                        int note_vel = Pm_MessageData2(buffer[i].message);
                        int note_index = note_to_last_notes[note_num];
                        if(note_index >= 0) {
                            notes[note_index].time_from_noteoff = 0;
                            notes[note_index].released = true;
                            notes[note_index].noteoff_velocity = 64;
                            note_to_last_notes[note_num] = -1;
                        }
                        if(note_vel > 0) {
                            notes[num_notes].frequency = note_frequencies[note_num];
                            notes[num_notes].time_from_noteon = 0;
                            notes[num_notes].pressed = true;
                            notes[num_notes].noteon_velocity = note_vel;
                            notes[num_notes].sampling_position = 0;
                            notes[num_notes].reached_end = false;
                            note_channel[num_notes] = Pm_MessageStatus(buffer[i].message) & 0x0f;
                            note_to_last_notes[note_num] = num_notes;
                            num_notes = (num_notes + 1) % POLYPHONY;
                        }
                    } else if ((Pm_MessageStatus(buffer[i].message) & 0xf0) == 0x80) {
                        int note_num = Pm_MessageData1(buffer[i].message) & 0x7f;
                        int note_vel = Pm_MessageData2(buffer[i].message) & 0x7f;
                        int note_index = note_to_last_notes[note_num];
                        if(note_index >= 0) {
                            notes[note_index].time_from_noteoff = 0;
                            notes[note_index].noteoff_velocity = note_vel;
                            notes[note_index].released = true;
                            note_to_last_notes[note_num] = -1;
                        }
                    } else if ((Pm_MessageStatus(buffer[i].message) & 0xf0) == 0xB0) {
                        int control_num = Pm_MessageData1(buffer[i].message) & 0x7f;
                        int control_val = Pm_MessageData2(buffer[i].message) & 0x7f;
                        int channel = Pm_MessageStatus(buffer[i].message) & 0x0f;
                        controls[channel][control_num] = control_val;
                    } else {
                        fprintf(stderr, "%d, %d, %d\n", Pm_MessageStatus(buffer[i].message), Pm_MessageData1(buffer[i].message), Pm_MessageData2(buffer[i].message));
                    }
                }
            } else if(len < 0) {
                fprintf(stderr, "err: %s\n", Pm_GetErrorText(err));
                return EXIT_FAILURE;
            }
        } else if(poll < 0) {
            fprintf(stderr, "err: %s\n", Pm_GetErrorText(err));
            return EXIT_FAILURE;
        }
        usleep(5000);
    }
    
    Pa_StopStream(audio_stream);
    Pa_CloseStream(audio_stream);
    Pa_Terminate();

    Pm_Close(midi_stream);
    Pm_Terminate(); 
    return EXIT_SUCCESS;
}
