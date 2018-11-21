#include <stdio.h>
#include <iostream>
#include <string.h>
#include <cstdio>
#include <cmath>
#include <stdlib.h>
#include "audio_augmentation_impulse.h"
#define CLOCKSIZE 44100 * 2

using namespace std;

char name[40];
short int value[CLOCKSIZE * 5];
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

void make_impulse(int num, int len, int power){
	int idx, samples_count = 0, sample_size;
	int cnt = 0;
	FILE *fin, *fout;
	wav_header_t header;
	chunk_t chunk;
	unsigned long chunk_size;

	//load big data
	sprintf(name, "./input/audio/audio (%d).wav", num);
	fin = fopen(name, "rb");
	sprintf(name, "./output/mixed_sound_%d-%d-%d.wav", num, len, power);
	fout = fopen(name, "wb");
	//load header and chunk
	fread(&header, sizeof(header), 1, fin);
	printWAVHeader(header);

	//go to fin1's audio data
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

	fwrite(&header, sizeof(header), 1, fout);
	fwrite(&chunk, sizeof(chunk), 1, fout);

	//load audio data
	for (idx = 0; idx < CLOCKSIZE * 3; idx++){
		fread(&value[idx], sample_size, 1, fin);
	}
	for (idx = 0; idx < CLOCKSIZE * 3; idx++){
		////////////////////////////////////////////////////¹Ù²ãÁà¾ßÇÑ´Ù¹Ù²ãÁà¾ßÇÑ´Ù. len°ªÀÌ¶û powerÀÌ¶û 100À¸·Î ³ª´²ÁÖ´Â°Í°°Àº ¼¶¼¼ÇÑ¾Öµé ´Ù ¹Ù²ãÁà¾ßÇÑ´ç¸¶¤Ó;¤Ã¤·¤¤¸¶¤Ó¤Ã¤«¤¤ÀÌ¤Ã¤¿¤¤¤±¤·¶ó¤Ó¤Ã¤·
		if (idx < len){
			changed_value[idx] = value[idx];
		}
		else{
			changed_value[idx] = value[idx] + value[idx - len] * power / 100;
		}
	}
	for (idx = 0; idx < CLOCKSIZE * 3; idx++){
		fwrite(&changed_value[idx], sample_size, 1, fout);
	}
	fclose(fin);
	fclose(fout);
}

