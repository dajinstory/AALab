#include <stdio.h>
#include "sound_augmentation.h"

int main(){
	int num_of_files = 100;
	for (int i = 1; i <= num_of_files; i++){
		volume_aug(i, POWERLEVEL);
	}
	return 0;
}