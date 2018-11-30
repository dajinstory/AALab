#include "audio.h"
#include <iostream>
#include <time.h>
using namespace std;

char name[40];
short int impulse_data[READSIZE*AUDIOTIME];
audio back_classroom;
audio audioData;

int main(){
	back_classroom.readWAV("classroom.wav");
	audioData.readWAV("speech2.wav");
	clock_t begin, end;
	begin = clock();
	back_classroom.conv(audioData.returnValue(), impulse_data);
	end = clock();
	cout << "수행시간: " << ((end - begin) / CLOCKS_PER_SEC) << endl;
	begin = clock();
	audioData.writeWav("out.wav", impulse_data);
	end = clock();
	cout << "수행시간: " << ((end - begin) / CLOCKS_PER_SEC) << endl;

	return 0;
}
