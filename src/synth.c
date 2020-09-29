
#include <portaudio.h>
#include <stdio.h>
#include <stdint.h>

#include "simple.h"

#define SAMPLE_RATE 44100
#define CHANNELS 2
#define BIT_SIZE 16

SimpleWaveSynthParameters params = {SAMPLE_RATE, 100, 0.5};
int sample = 0;

int audioCallback(const void* input, void* output, uint64_t frame_count, const PaStreamCallbackTimeInfo* time_info, PaStreamCallbackFlags status_flage, void* user_data) {
    float (*out)[CHANNELS] = (float(*)[CHANNELS])output;
    for(int s = 0; s < frame_count; s++) {
        for(int c = 0; c < CHANNELS; c++) {
            //out[s][c] = simpleSineWaveSynth(&params, sample);
            // out[s][c] = simpleSquareWaveSynth(&params, sample);
            out[s][c] = simpleTriangleWaveSynth(&params, sample);
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
    
    fprintf(stderr, "Press enter to stop....\n");
    getc(stdin);
    
    Pa_StopStream(audio_stream);
    Pa_CloseStream(audio_stream);
    Pa_Terminate();
    return 0;
}
