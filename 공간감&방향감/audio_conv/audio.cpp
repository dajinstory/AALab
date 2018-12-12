
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include "audio.h"

using namespace std;

audio::audio(void){
	
}
audio::audio(char* filename){
	readWAV(filename);
}

void audio::printWAVHeader(void){
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
}

void audio::readWAV(char* filename){
	FILE *fin;
	int samples_count, sample_size;

	fin = fopen(filename, "rb");

	//load header and chunk
	fread(&header, sizeof(header), 1, fin);
	while (true)
	{
		fread(&chunk, sizeof(chunk), 1, fin);
		printf("%c%c%c%c\t" "%u\n", chunk.ID[0], chunk.ID[1], chunk.ID[2], chunk.ID[3], chunk.size);
		if (*(unsigned int *)&chunk.ID == 0x61746164)
			break;
		//skip chunk data bytes
		fseek(fin, chunk.size, SEEK_CUR);
	}
	sample_size = header.bitsPerSample / 8;
	printWAVHeader();

	//read (44100 x time) data
	for (int i = 0; i < READSIZE * AUDIOTIME; i++){		
		fread(&value[i], sample_size, 1, fin);
	}
	fclose(fin);
}

short int* audio::returnValue(void){
	return value;
}
void audio::conv(short int* arr, short int* result){
	for (int i = 0; i < READSIZE*AUDIOTIME; i++){
		int sum = 0, back_start=1;
		if (i % 2 == 0){
			back_start = 0;
		}
		else{
			back_start = 1;
		}
		for (int data_idx = i, back_idx = back_start; data_idx >= 0; data_idx -= 2, back_idx += 2){
			sum += arr[data_idx] * value[back_idx];
		}
		if (sum > 32767 || sum < -32768);// printf("overflow!!!!!!!!\n");
		result[i] = (short int)sum;
	}
}
void audio::writeWav(char* filename, short int* result){
	FILE *fout;
	int sample_size = header.bitsPerSample / 8;
	fout = fopen("out.wav", "wb");
	fwrite(&header, sizeof(header), 1, fout);
	fwrite(&chunk, sizeof(chunk), 1, fout);
	for (int i = 0; i < READSIZE * AUDIOTIME; i++){
		fwrite(&value[i], sample_size, 1, fout);
	}
	fclose(fout);
}
