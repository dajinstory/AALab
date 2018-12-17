```
# Data Augmentation tool
─ augio_sound_augmentation
  ├ sound_augmentation.cpp           
  ├ sound_augmentation.h           
  ├ Source.cpp 					       		# main function. run this      
  ├ input
  │ ├ header_format.wav 			        # .wav header format
  │ ├ audio (1).wav 				        # input audio data
  │ ├ ...
  │ └ audio (N).wav 				        # N is the # of audio data
  └ output 							        # augmentated data
  	├ audio-1-1.wav
  	├ ...
  	└ audio-N-M.wav 						# M is the num of divided audio files from audio (N).wav
```

``
The length of input audio files must be fixed
``

1. modify 
`	int num_of_files = 100;`
in Source.cpp for your environment

2. modify `sprintf(name, "./input/audio (%d).wav", num);`, `sprintf(name, "./output/audio-%d-%d.wav", num, volume);` in audio_divider.cpp for your environment

3. if you want to edit the file with different file length or different volume changes, modify 
`
#define TIME_S 3
#define POWERLEVEL 5
` in sound_augmentation.h

4. run Source.cpp
