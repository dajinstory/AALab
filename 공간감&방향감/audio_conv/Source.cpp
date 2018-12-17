#include "audio.h"
#include <iostream>
using namespace std;

char name[40];
short int impulse_data[READSIZE*AUDIOTIME];
audio back_classroom;
audio audioData;

int main(){
	back_classroom.readWAV("./background/classroom.wav");
	audioData.readWAV("./input/speech2.wav");
	back_classroom.conv(audioData.returnValue(), impulse_data);
	audioData.writeWav("./output/out.wav", impulse_data);
	return 0;
}
