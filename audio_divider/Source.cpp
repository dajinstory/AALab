#include <stdio.h>
#include "audio_divider.h"

int main(){
	int num_of_files = 2;
	for (int i = 1; i <= num_of_files; i++){
		divide_audio(i, 3);
	}
	return 0;
}