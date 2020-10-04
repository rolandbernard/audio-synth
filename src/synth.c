
#include <portmidi.h>
#include <portaudio.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <math.h>
#include <limits.h>
#include <stdlib.h>

#include "simple.h"
#include "compination.h"
#include "ahdsr.h"

#define SAMPLE_RATE 44100
#define CHANNELS 2
#define BIT_SIZE 16
#define POLYPHONY 256

SynthEnviormentData env = { SAMPLE_RATE };
SimpleWaveSynthInstrumentData params = { 0.1 };
SynthInstrumentData* instr_data[] = { (SynthInstrumentData*)&params, (SynthInstrumentData*)&params,  (SynthInstrumentData*)&params};
SynthInstrumentFunction instr_func[] = { (SynthInstrumentFunction)simpleSineWaveSynth, (SynthInstrumentFunction)simpleTriangleWaveSynth, (SynthInstrumentFunction)simpleSquareWaveSynth };
MultiAdditiveInstrumentData addit = {
    .instrument_count = 2,
    .base_instrument_data = instr_data,
    .base_instrument_function = instr_func,
};
float delays[] = { 0.0, 0.05, 0.1 };
MultiDelayEffectData delay = {
    .base_instrument_data = (SynthInstrumentData*)&addit,
    .base_instrument_function = (SynthInstrumentFunction)multiAdditiveInstrument,
    .delay_count = sizeof(delays)/sizeof(delays[0]),
    .delays = delays,
};
float multipl[] = { 0.125, 0.25, 0.5, 1.0, 2.0, 4.0, 8.0, 16.0 };
MultiOctaveEffectData effect = {
    .base_instrument_data = (SynthInstrumentData*)&delay,
    .base_instrument_function = (SynthInstrumentFunction)multiDelayEffect,
    .multiplier_count = sizeof(multipl)/sizeof(multipl[0]),
    .multipliers = multipl,
};
AhdsrEnvelopeData instrument = {
    .base_instrument_data = (SynthInstrumentData*)&effect,
    .base_instrument_function = (SynthInstrumentFunction)multiOctaveEffect,
    .delay = 0.0,
    .attack = 0.05,
    .hold = 0.2,
    .decay = 1.0,
    .sustain = 0.5,
    .release = 0.5,
};
int sample = 0;

int num_notes = 0;
SynthNoteData notes[POLYPHONY];
int note_to_last_notes[128];

int audioCallback(const void* input, void* output, uint64_t frame_count, const PaStreamCallbackTimeInfo* time_info, PaStreamCallbackFlags status_flage, void* user_data) {
    float (*out)[CHANNELS] = (float(*)[CHANNELS])output;
    for(int s = 0; s < frame_count; s++) {
        // out[s][c] = simpleSineWaveSynth(&params, sample);
        // out[s][c] = simpleSquareWaveSynth(&params, sample);
        // float v = simpleTriangleWaveSynth(&params, sample);
        float v = 0;
        for(int i = 0; i < POLYPHONY; i++) {
            if(!notes[i].reached_end) {
                v += ahdsrEnvelope(&env, &instrument, &notes[i]);
                notes[i].sample_from_noteon++;
                if(notes[i].sample_from_noteoff >= 0) {
                    notes[i].sample_from_noteoff++;
                }
            }
        }
        for(int c = 0; c < CHANNELS; c++) {
            out[s][c] = v / 30;
        }
        sample++;
    }
    return 0;
}

int main(int argc, char** argv) {
    for(int i = 0; i < POLYPHONY; i++) {
        notes[i].sample_from_noteoff = -1;
        notes[i].sample_from_noteon = -1;
        notes[i].reached_end = true;
    }
    for(int i = 0; i < 128; i++) {
        note_to_last_notes[i] = -1;
    }

    PaStream* audio_stream;
    freopen("/dev/null","w",stderr);
    Pa_Initialize(); 
    freopen("/dev/tty","w",stderr);
    Pa_OpenDefaultStream(&audio_stream, 0, CHANNELS, paFloat32, SAMPLE_RATE, paFramesPerBufferUnspecified, audioCallback, NULL);
    Pa_StartStream(audio_stream);
    
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
                        if(note_vel == 0) {
                            int note_index = note_to_last_notes[note_num];
                            if(note_index >= 0) {
                                notes[note_index].sample_from_noteoff = 0;
                                notes[note_index].noteoff_velocity = 64;
                            }
                        } else {
                            notes[num_notes].frequency = note_frequencies[note_num];
                            notes[num_notes].sample_from_noteon = 0;
                            notes[num_notes].sample_from_noteoff = -1;
                            notes[num_notes].noteon_velocity = note_vel;
                            notes[num_notes].reached_end = false;
                            note_to_last_notes[note_num] = num_notes;
                            num_notes = (num_notes + 1) % POLYPHONY;
                        }
                    } else if ((Pm_MessageStatus(buffer[i].message) & 0xf0) == 0x80) {
                        int note_num = Pm_MessageData1(buffer[i].message);
                        int note_vel = Pm_MessageData2(buffer[i].message);
                        int note_index = note_to_last_notes[note_num];
                        if(note_index >= 0) {
                            notes[note_index].sample_from_noteoff = 0;
                            notes[note_index].noteoff_velocity = note_vel;
                        }
                    } else {
                        fprintf(stderr, "%hhu, %hhu, %hhu\n", Pm_MessageStatus(buffer[i].message), Pm_MessageData1(buffer[i].message), Pm_MessageData2(buffer[i].message));
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

    Pm_Close(midi_stream);
    Pm_Terminate(); 
    
    Pa_StopStream(audio_stream);
    Pa_CloseStream(audio_stream);
    Pa_Terminate();
    return EXIT_SUCCESS;
}
