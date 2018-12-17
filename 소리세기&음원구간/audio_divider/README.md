```
# Data Augmentation tool
─ augio_divider
  ├ audio_divider.cpp           
  ├ audio_divider.h           
  ├ Source.cpp 					        	# main function. run this      
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
The length of input audio files is not matter.
``

1. modify 
`int num_of_files = 139, section_length = 3, section_interval = 5;`
in Source.cpp for your environment

2. modify `sprintf(name, "./input/audio (%d).wav", num);`, `		sprintf(name, "./output/audio-%d-%d.wav", num, idx);` in audio_divider.cpp for your environment

3. run Source.cpp
