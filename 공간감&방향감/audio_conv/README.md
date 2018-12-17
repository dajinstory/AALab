```
# Data Augmentation tool
─ augio_conv
  ├ audio.cpp           
  ├ audio.h           
  ├ wav.h                       # audio class is here
  ├ Source.cpp 					       	# main function. run this      
  ├ input
  │ ├ audio (1).wav 				    # input audio data
  │ ├ ...
  │ └ audio (N).wav 				    # N is the # of audio data
  ├ background                  # background files are here
  └ output 							        # augmentated data
```

``
The length of input audio files must be fixed
``

1. modify
`
back_classroom.readWAV("./background/classroom.wav");
audioData.readWAV("./input/speech2.wav");
audioData.writeWav("./output/out.wav", impulse_data);
` in Source.cpp
change the file path.

2. if the length of input audio file and background file is not 3s,
modify `#define AUDIOTIME 3` in audio.h


3. run Source.cpp
