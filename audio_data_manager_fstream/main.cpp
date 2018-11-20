#include <iostream>
#include <stdio.h>
#include <string>
#include "audio_manager_fstream.h"
using namespace std;

int main(){
	string filename_hf_s = "./header_format/header_format.wav";
	char* filename_hf_c = &filename_hf_s[0u];

	string filename_txt = "./txt/audio";
	string filetype_txt = ".txt";
	string filename_txt_s;
	char* filename_txt_c;

	string filename_wav = "./wav/audio";
	string filetype_wav = ".wav";
	string filename_wav_s;
	char* filename_wav_c;

	char tmp[65] = { 0 };
	string number;

	for (int i = 2; i <= 2; i++) {
		itoa(i, tmp, 10);
		number = string(tmp);
		filename_txt_s = filename_txt + number + filetype_txt;
		filename_txt_c = &filename_txt_s[0u];
		filename_wav_s = filename_wav + number + filetype_wav;
		filename_wav_c = &filename_wav_s[0u];
		//function
		//wav_to_txt(filename_wav_c, filename_txt_c);
		txt_to_wav(filename_hf_c, filename_txt_c, filename_wav_c);
	}
	return 0;
}