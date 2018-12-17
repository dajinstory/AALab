```
# Data Augmentation tool
─ augio_mix
  ├ audio_mix.cpp           
  ├ audio_mix.h           
  ├ Source.cpp 					       		        # main function. run this      
  ├ input
  │ ├ audio    
  │ │ ├ audio (1).wav                     # input audio data
  │ │ ├ ...
  │ │ └ audio (N).wav                     # N is the # of audio data
  │ └ background                 
  │   ├ background (1).wav                # input background data
  │   ├ ...
  │   └ background (M).wav                # M is the # of background data
  └ output 							                  # augmentated data
  	├ audio-1-1.wav
  	├ ...
  	└ audio-N-M.wav 						# M is the num of divided audio files from audio (N).wav
```

``
The length of input audio files must be fixed
``

1. modify 
`int num_of_audio = 1, num_of_backgrounds = 1;`
in Source.cpp for your environment

2. modify `converge_audio(i, j, 20, 1);` in Source.cpp. change "20, 1" to other ratio

3. modify 
`
sprintf(name, "./input/audio/audio (%d).wav", num1);
fin1 = fopen(name, "rb");
sprintf(name, "./input/background/background (%d).wav", num2);
fin2 = fopen(name, "rb");
sprintf(name, "./output/mixed_sound_%d-%d(%d-%d).wav", num1, num2, r1, r2);
fout = fopen(name, "wb");
` in audio_mix.cpp.

4. if you want to edit the file with different file length or different volume changes, modify 
`
#define TIME_S 3
` in audio_mix.h

4. run Source.cpp
