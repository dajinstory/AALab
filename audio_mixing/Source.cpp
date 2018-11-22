#include <stdio.h>
#include "audio_augmentation_2.h"
#define CLOCKSIZE 44100 * 2 //1초당 data 개수

int main(){
	int num_of_audio = 1, num_of_backgrounds = 1;
	for (int i = 1; i <= num_of_audio; i++){
		for (int j = 1; j <= num_of_backgrounds; j++){
			converge_audio(i, j, 20, 1);
		}
	}
	return 0;
}