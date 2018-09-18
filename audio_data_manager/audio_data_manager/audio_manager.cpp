#include <iostream>
#include <cstdio>
#include <cmath>
#include "audio_manager.h"

#define READSIZE 2048

using namespace std;

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
}

void wav_to_txt(const char* fileName_wav, const char* fileName_txt){
	//Load file pointer
	FILE *fin = fopen(fileName_wav, "rb");
	FILE *fout = fopen(fileName_txt, "w+");

	//Read WAV header
	wav_header_t header;
	fread(&header, sizeof(header), 1, fin);

	//Print WAV header
	printWAVHeader(header);

	//Read chunk file
	chunk_t chunk;
	unsigned long chunk_size;
	while (true)
	{
		fread(&chunk, sizeof(chunk), 1, fin);
		printf("%c%c%c%c\t" "%u\n", chunk.ID[0], chunk.ID[1], chunk.ID[2], chunk.ID[3], chunk.size);
		if (*(unsigned int *)&chunk.ID == 0x61746164)
			break;
		//skip chunk data bytes
		fseek(fin, chunk.size, SEEK_CUR);
	}
	chunk_size = chunk.size;


	//get Number of samples
	int sample_size = header.bitsPerSample / 8;
	int samples_count = chunk_size * 8 / header.bitsPerSample;
	printf("size of audio : %d\n", samples_count);


	//Reading audio data
	int start = 0;
	short int value[READSIZE];
	for (int s = 0; s < samples_count; s += READSIZE){
		for (int i = 0; i < READSIZE && s + i < samples_count; i++)
		{
			fread(&value[i], sample_size, 1, fin);
		}
		for (int i = 0; i < READSIZE && s + i < samples_count; i++){
			fprintf(fout, "%hd\n", value[i]);
			//fwrite(&value[i], sample_size, 1, fout);
		}
	}
	fclose(fin);
	fclose(fout);
}

void txt_to_wav(const char* header_format, const char* fileName_txt, const char* fileName_wav){
	//Load file pointer
	FILE *hf = fopen(header_format, "rb");
	FILE *fin = fopen(fileName_txt, "r");
	FILE *fout = fopen(fileName_wav, "wb");

	//Read WAV header
	wav_header_t header;
	fread(&header, sizeof(header), 1, hf);

	//Print WAV header
	printWAVHeader(header);

	//Read chunk file
	chunk_t chunk;
	unsigned long chunk_size;
	while (true)
	{
		fread(&chunk, sizeof(chunk), 1, hf);
		printf("%c%c%c%c\t" "%u\n", chunk.ID[0], chunk.ID[1], chunk.ID[2], chunk.ID[3], chunk.size);
		if (*(unsigned int *)&chunk.ID == 0x61746164)
			break;
		//skip chunk data bytes
		fseek(hf, chunk.size, SEEK_CUR);
	}
	chunk_size = chunk.size;

	//get Number of samples
	int sample_size = header.bitsPerSample / 8;
	int samples_count = chunk_size * 8 / header.bitsPerSample;
	printf("size of audio : %d\n", samples_count);

	//Writing audio data
	fwrite(&header, sizeof(header), 1, fout);
	fwrite(&chunk, sizeof(chunk), 1, fout);
	int num = 0, idx = 0;
	short int value[READSIZE];

	while (1){
		for (idx = 0; idx < READSIZE && feof(fin) == 0; idx++){
			//fread(&value[idx], sample_size, 1, fin);
			fscanf(fin, "%hd", &value[idx]);
		}
		for (int i = 0; i < idx; i++){
			fwrite(&value[i], sample_size, 1, fout);
		}
		num += idx;
		if (feof(fin) != 0){
			break;
		}
	}
	samples_count = num;

	//Renew number of samples
	header.chunkSize = samples_count * 2 + 36;
	chunk.size = samples_count * 2;
	fseek(fout, 0, SEEK_SET);
	fwrite(&header, sizeof(header), 1, fout);
	fwrite(&chunk, sizeof(chunk), 1, fout);


	fclose(hf);
	fclose(fin);
	fclose(fout);
}
