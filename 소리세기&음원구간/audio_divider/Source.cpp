#include <stdio.h>
#include "audio_divider.h"

int main(){
	int num_of_files = 139, section_length = 3, section_interval = 5;//if section_interval==5, it means 0.5sec
	for (int i = 1; i <= num_of_files; i++){
		divide_audio(i, section_length, CLOCKSIZE/10*section_interval);
	}
	return 0;
}