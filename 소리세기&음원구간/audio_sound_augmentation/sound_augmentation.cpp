#include <stdio.h>
#include <iostream>
#include <string.h>
#include <cstdio>
#include <cmath>
#include <stdlib.h>
#include "sound_augmentation.h"

using namespace std;

char name[40];
short int value[CLOCKSIZE*100];
short int increased_value[CLOCKSIZE * 100];
short int changed_value[CLOCKSIZE * 100];

void printWAVHeader(wav_header_t header){
	printf("WAV File Header read:\n");
	printf("File Type: %s\n", header.chunkID);
	printf("File Size: %ld\n", header.chunkSize);
	printf("WAV Marker: %s\n", header.format);
	printf("Format Name: %s\n", header.subchunk1ID);
	printf("Format Length: %ld\n", header.subchunk1Size);
	printf("Format Type: %hd\n", header.audioFormat);
	printf("Number of Channels: %hd\n", header.numChannels);
	printf("Sample Rate: %ld\n", header.sampleRate);
	printf("Sample Rate * Bits/Sample * Channels / 8: %ld\n", header.byteRate);
	printf("Bits per Sample * Channels / 8.1: %hd\n", header.blockAlign);
	printf("Bits per Sample: %hd\n", header.bitsPerSample);
	printf("\n");
}

void volume_aug(int num, int volumes){
	int idx, samples_count = 0, sample_size;
	int cnt = 0;
	FILE *fin;
	wav_header_t header;
	chunk_t chunk;
	unsigned long chunk_size;

	//load big data
	//change "D:\\database\\3s_speech\\3s_speech-%d.wav" to your local path to load
	//the length of input audio files must be fixed.
	//sprintf(name, "D:\\database\\3s_speech\\3s_speech-%d.wav", num);
	sprintf(name, "./input/audio (%d).wav", num);
	fin = fopen(name, "rb");

	//load header and chunk
	fread(&header, sizeof(header), 1, fin);
	printWAVHeader(header);

	while (true)
	{
		fread(&chunk, sizeof(chunk), 1, fin);
		printf("%c%c%c%c\t%u\n",chunk.ID[0], chunk.ID[1], chunk.ID[2], chunk.ID[3], chunk.size);
		if (*(unsigned int *)&chunk.ID ==0x61746164)
			break;
		if (chunk.ID[2] == 'd' && chunk.ID[3] == 'a'){
			fseek(fin, -6, SEEK_CUR);
			continue;
		}
		//skip chunk data bytes
		fseek(fin, chunk.size, SEEK_CUR);
	}
	sample_size = header.bitsPerSample / 8;
	printWAVHeader(header);

	//load audio data
	for (idx = 0; idx < CLOCKSIZE * TIME_S; idx++){
		fread(&value[idx], sample_size, 1, fin);
	}
	
	//to avoid overflow, make the audio data to maximum volume, and then decrease.
	short int max_value = 0;
	for (int i = 0; i < CLOCKSIZE * TIME_S; i++){
		short int tmp = value[i];
		if (tmp < 0)tmp = -tmp;
		if (tmp > max_value)max_value = tmp;
	}
	for (int i = 0; i < CLOCKSIZE * TIME_S; i++){
		int tmp = (int)value[i];
		tmp *= SHORTINT_MAX;
		tmp /= max_value;
		increased_value[i] = (short int)tmp;
	}
		
	for (int volume = 1; volume <= POWERLEVEL; volume++){
		//load directory to be saved
		FILE *fout;
		//change "D:\\database\\output\\3s_speech\\3s_speech-%d-%d.wav" to your local path to save
		//sprintf(name, "D:\\database\\output\\3s_speech\\3s_speech-%d-%d.wav", num, volume);
		sprintf(name, "./output/audio-%d-%d.wav", num, volume);

		fout = fopen(name, "wb");

		//write header and chunk
		fwrite(&header, sizeof(header), 1, fout);
		fwrite(&chunk, sizeof(chunk), 1, fout);



		//write audio data
		int maxpower = 1, nowpower = 1;
		for (int i = 0; i < POWERLEVEL; i++){
			maxpower *= POWERLEVEL + 1 - i;
		}
		for (int i = 0; i < volume; i++){
			nowpower *= POWERLEVEL + 1 - i;
		}
		for (int i = 0; i < CLOCKSIZE * TIME_S; i++){
			long long tmp = (long long)increased_value[i];
			tmp *= nowpower;
			tmp /= maxpower;
			changed_value[i] = (short int)tmp;
			fwrite(&changed_value[i], sample_size, 1, fout);
		}
		fclose(fout);
	}
	fclose(fin);
}

