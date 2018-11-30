
#define READSIZE 44100 * 2
#define AUDIOTIME 3
#include "wav.h"

class audio{
private:
	short int value[READSIZE * AUDIOTIME];
	wav_header_t header;
	chunk_t chunk;
public:
	audio(void);
	audio(char* filename);
	void readWAV(char* filename);
	short int* returnValue(void);
	void printWAVHeader(void);
	void conv(short int *arr, short int* result);
	void writeWav(char* filename, short int* result);
};