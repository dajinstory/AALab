#include <stdio.h>
#include "audio_augmentation.h"
#define CLOCKSIZE 44100 * 2 //1�ʴ� data ����

int main(){
	int num_of_files = 1;
	int div = 5; //0.5�ʰ��� �ٸ� ���� ��ġ��
	int time_for_each_files = 3;
	for (int i = 1; i <= num_of_files; i++){
		divide_audio(i, time_for_each_files, CLOCKSIZE * div / 10);
	}
	return 0;
}