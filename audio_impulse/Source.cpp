#include <stdio.h>
#include "audio_augmentation_impulse.h"
#define CLOCKSIZE 44100 * 2 //1�ʴ� data ����

int main(){
	int num_of_audio = 1;
	for (int i = 1; i <= num_of_audio; i++){
		for (int len = 1; len <= 3; len++){
			for (int strength = 1; strength <= 3; strength++){
				make_impulse(i, len, strength);
			}
		}
	}
	return 0;
}