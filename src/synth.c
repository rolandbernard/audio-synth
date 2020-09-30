
#include <portmidi.h>
#include <portaudio.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <math.h>
#include <limits.h>

#include "simple.h"

#define SAMPLE_RATE 44100
#define CHANNELS 2
#define BIT_SIZE 16

SimpleWaveSynthParameters params = {SAMPLE_RATE, 0.5};
int sample = 0;

typedef struct {
    float frequency;
    long sample;
} NoteInformation;

int num_notes = 0;
volatile NoteInformation notes[127];

int audioCallback(const void* input, void* output, uint64_t frame_count, const PaStreamCallbackTimeInfo* time_info, PaStreamCallbackFlags status_flage, void* user_data) {
    float (*out)[CHANNELS] = (float(*)[CHANNELS])output;
    for(int s = 0; s < frame_count; s++) {
        // out[s][c] = simpleSineWaveSynth(&params, sample);
        // out[s][c] = simpleSquareWaveSynth(&params, sample);
        // float v = simpleTriangleWaveSynth(&params, sample);
        float v = 0;
        for(int i = 0; i < 127; i++) {
            if(notes[i].sample >= 0) {
                v += simpleSineWaveSynth(&params, powf(2, (i - 69.0) / 12.0) * 440, notes[i].sample++);
            }
        }
        for(int c = 0; c < CHANNELS; c++) {
            out[s][c] = v;
        }
        sample++;
    }
    return 0;
}

int main(int argc, char** argv) {
    PaStream* audio_stream;
    freopen("/dev/null","w",stderr);
    Pa_Initialize(); 
    freopen("/dev/tty","w",stderr);
    Pa_OpenDefaultStream(&audio_stream, 0, CHANNELS, paFloat32, SAMPLE_RATE, paFramesPerBufferUnspecified, audioCallback, NULL);
    Pa_StartStream(audio_stream);
    
    Pm_Initialize();
    PortMidiStream* midi_stream;
    PmError err = Pm_OpenInput(&midi_stream, 3, NULL, 64, NULL, NULL);
    if(err) {   
        fprintf(stderr, "err: %s\n", Pm_GetErrorText(err));
    }
    for(int i = 0; i < 127; i++) {
        notes[i].sample = LONG_MIN;
    }

    for(;;) {
        PmError poll = Pm_Poll(midi_stream);
        if(poll > 0) {
            PmEvent buffer[64];
            int len = Pm_Read(midi_stream, buffer, 64);
            if(len > 0) {
                for (int i = 0; i < len; i++) {
                    if ((Pm_MessageStatus(buffer[i].message) & 0xf0) == 0x90) {
                        notes[Pm_MessageData1(buffer[i].message)].sample = 0;
                    } else if ((Pm_MessageStatus(buffer[i].message) & 0xf0) == 0x80) {
                        notes[Pm_MessageData1(buffer[i].message)].sample = LONG_MIN;
                    } else {
                        fprintf(stderr, "%hhu, %hhu, %hhu\n", Pm_MessageStatus(buffer[i].message), Pm_MessageData1(buffer[i].message), Pm_MessageData2(buffer[i].message));
                    }
                }
            } else if(len < 0) {
                fprintf(stderr, "err: %s\n", Pm_GetErrorText(err));
            }
        } else if(poll < 0) {
            fprintf(stderr, "err: %s\n", Pm_GetErrorText(err));
        }
        usleep(5000);
    }

    Pm_Close(midi_stream);
    Pm_Terminate(); 
    
    Pa_StopStream(audio_stream);
    Pa_CloseStream(audio_stream);
    Pa_Terminate();
    return 0;
}
