#include <stdio.h>
#include "audio_augmentation_impulse.h"
#define CLOCKSIZE 44100 * 2 //1초당 data 개수

int main(){
	int num_of_audio = 5;
	for (int i = 1; i <= num_of_audio; i++){
		for (int len = 1; len <= 1; len++){
			for (int strength = 1; strength <= 1; strength++){
				make_impulse(i, len, strength);
			}
		}
	}
	return 0;
}