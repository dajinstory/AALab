#include <stdio.h>
#include "audio_divider.h"

int main(){
	int num_of_files = 139, section_interval = 5;//(section_length=1) = 0.1sec
	for (int i = 1; i <= num_of_files; i++){
		divide_audio(i, 3, CLOCKSIZE/10*section_interval);
	}
	return 0;
}