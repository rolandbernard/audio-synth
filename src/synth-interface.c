
#include "synth-interface.h"

float note_frequencies[128] = {
    8.175798915643707, 8.661957218027252, 9.177023997418988, 9.722718241315029, 10.30086115352718, 10.91338223228137,
    11.56232570973857, 12.24985737442966, 12.97827179937328, 13.75000000000000, 14.56761754744030, 15.43385316425388, 
    16.35159783128741, 17.32391443605450, 18.35404799483797, 19.44543648263005, 20.60172230705436, 21.82676446456274,
    23.12465141947715, 24.49971474885932, 25.95654359874657, 27.50000000000000, 29.13523509488062, 30.86770632850775, 
    32.70319566257483, 34.64782887210901, 36.70809598967594, 38.89087296526011, 41.20344461410875, 43.65352892912548,
    46.24930283895430, 48.99942949771866, 51.91308719749314, 55.00000000000000, 58.27047018976124, 61.73541265701550, 
    65.40639132514966, 69.29565774421802, 73.41619197935188, 77.78174593052023, 82.40688922821750, 87.30705785825097,
    92.49860567790860, 97.99885899543733, 103.8261743949862, 110.0000000000000, 116.5409403795224, 123.4708253140310, 
    130.8127826502993, 138.5913154884360, 146.8323839587038, 155.5634918610404, 164.8137784564349, 174.6141157165019,
    184.9972113558172, 195.9977179908746, 207.6523487899725, 220.0000000000000, 233.0818807590449, 246.9416506280620, 
    261.6255653005986, 277.1826309768721, 293.6647679174076, 311.1269837220809, 329.6275569128699, 349.2282314330039,
    369.9944227116344, 391.9954359817492, 415.3046975799451, 440.0000000000000, 466.1637615180899, 493.8833012561241, 
    523.2511306011972, 554.3652619537442, 587.3295358348151, 622.2539674441618, 659.2551138257398, 698.4564628660078,
    739.9888454232688, 783.9908719634985, 830.6093951598903, 880.0000000000000, 932.3275230361799, 987.7666025122483, 
    1046.502261202394, 1108.730523907488, 1174.659071669630, 1244.507934888323, 1318.510227651479, 1396.912925732015,
    1479.977690846537, 1567.981743926997, 1661.218790319780, 1760.000000000000, 1864.655046072359, 1975.533205024496, 
    2093.004522404789, 2217.461047814976, 2349.318143339260, 2489.015869776647, 2637.020455302960, 2793.825851464031,
    2959.955381693075, 3135.963487853994, 3322.437580639561, 3520.000000000000, 3729.310092144719, 3951.066410048992, 
    4186.009044809578, 4434.922095629953, 4698.636286678520, 4978.031739553295, 5274.040910605920, 5587.651702928062,
    5919.910763386150, 6271.926975707989, 6644.875161279122, 7040.000000000000, 7458.620184289437, 7902.132820097988, 
    8372.018089619156, 8869.844191259906, 9397.272573357044, 9956.063479106590, 10548.08182121183, 11175.30340585612,
    11839.82152677230, 12543.85395141597,
};
