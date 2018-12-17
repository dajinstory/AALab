#include <stdio.h>
#include <iostream>
#include <string.h>
#include <cstdio>
#include <cmath>
#include <stdlib.h>
#include "audio_mix.h"
#define CLOCKSIZE 44100 * 2
#define TIME_S 3
using namespace std;

char name[40];
short int value_1[CLOCKSIZE * 5];
short int value_2[CLOCKSIZE * 5];
short int changed_value[CLOCKSIZE * 5];

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

void converge_audio(int num1, int num2, int r1, int r2){
	int idx, samples_count = 0, sample_size;
	int cnt = 0;
	FILE *fin1, *fin2, *fout;
	wav_header_t header;
	chunk_t chunk;
	unsigned long chunk_size;

	//load big data
	//change the path 
	sprintf(name, "./input/audio/audio (%d).wav", num1);
	fin1 = fopen(name, "rb");
	sprintf(name, "./input/background/background (%d).wav", num2);
	fin2 = fopen(name, "rb");
	sprintf(name, "./output/mixed_sound_%d-%d(%d-%d).wav", num1, num2, r1, r2);
	fout = fopen(name, "wb");
	//load header and chunk
	fread(&header, sizeof(header), 1, fin1);
	printWAVHeader(header);
	fread(&header, sizeof(header), 1, fin2);
	printWAVHeader(header);

	//go to fin1's audio data
	while (true)
	{
		fread(&chunk, sizeof(chunk), 1, fin1);
		printf("%c%c%c%c\t%u\n",chunk.ID[0], chunk.ID[1], chunk.ID[2], chunk.ID[3], chunk.size);
		if (*(unsigned int *)&chunk.ID ==0x61746164)
			break;
		if (chunk.ID[2] == 'd' && chunk.ID[3] == 'a'){
			fseek(fin1, -6, SEEK_CUR);
			continue;
		}
		//skip chunk data bytes
		fseek(fin1, chunk.size, SEEK_CUR);
	}
	sample_size = header.bitsPerSample / 8;
	
	//go to fin2's audio data
	while (true)
	{
		fread(&chunk, sizeof(chunk), 1, fin2);
		printf("%c%c%c%c\t%u\n", chunk.ID[0], chunk.ID[1], chunk.ID[2], chunk.ID[3], chunk.size);
		if (*(unsigned int *)&chunk.ID == 0x61746164)
			break;
		if (chunk.ID[2] == 'd' && chunk.ID[3] == 'a'){
			fseek(fin2, -6, SEEK_CUR);
			continue;
		}
		//skip chunk data bytes
		fseek(fin2, chunk.size, SEEK_CUR);
	}

	fwrite(&header, sizeof(header), 1, fout);
	fwrite(&chunk, sizeof(chunk), 1, fout);

	//load audio data
	for (idx = 0; idx < CLOCKSIZE * TIME_S; idx++){
		fread(&value_1[idx], sample_size, 1, fin1);
		fread(&value_2[idx], sample_size, 1, fin2);
	}
	for (idx = 0; idx < CLOCKSIZE * TIME_S; idx++){
		int v1, v2;
		v1 = (int)value_1[idx];
		v2 = (int)value_2[idx];
		changed_value[idx] = (short int)((v1*r1 + v2*r2) / (r1 + r2));
	}
	for (idx = 0; idx < CLOCKSIZE * TIME_S; idx++){
		fwrite(&changed_value[idx], sample_size, 1, fout);
	}
	fclose(fin1);
	fclose(fin2);
	fclose(fout);
}

