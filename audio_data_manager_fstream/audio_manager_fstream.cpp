#include <iostream>
#include <fstream>
#include <cstdio>
#include <cmath>
#include "audio_manager_fstream.h"

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
	//rb+ 인 경우는 수정하고싶을때.
	//Load file pointer
	ifstream inFile(fileName_wav, ios::binary);
	ofstream outFile(fileName_txt);

	//Read WAV header
	wav_header_t header;
	inFile.read(reinterpret_cast<char*>(&header), sizeof(wav_header_t));

	//Print WAV header
	printWAVHeader(header);

	//Read chunk file
	chunk_t chunk;
	unsigned long chunk_size;
	while (true)
	{
		inFile.read(reinterpret_cast<char*>(&chunk), sizeof(chunk_t));
		printf("%c%c%c%c\t" "%u\n", chunk.ID[0], chunk.ID[1], chunk.ID[2], chunk.ID[3], chunk.size);
		if (*(unsigned int *)&chunk.ID == 0x61746164)
			break;
		//skip chunk data bytes
		inFile.seekg(chunk.size, ios::cur);
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
			inFile.read(reinterpret_cast<char*>(&value[i]), sizeof(short int));
		}
		for (int i = 0; i < READSIZE && s + i < samples_count; i++){
			outFile << value[i] << endl;
		}
	}
	inFile.close();
	outFile.close();
}

void txt_to_wav(const char* header_format, const char* fileName_txt, const char* fileName_wav){
	//Load file pointer
	ifstream hf(header_format, ios::binary);
	ifstream inFile(fileName_txt);
	ofstream outFile(fileName_wav, ios::binary);

	//Read WAV header
	wav_header_t header;
	hf.read(reinterpret_cast<char*>(&header), sizeof(wav_header_t));

	//Print WAV header
	printWAVHeader(header);

	//Read chunk file
	chunk_t chunk;
	unsigned long chunk_size;
	while (true)
	{
		hf.read(reinterpret_cast<char*>(&chunk), sizeof(chunk_t));
		printf("%c%c%c%c\t" "%u\n", chunk.ID[0], chunk.ID[1], chunk.ID[2], chunk.ID[3], chunk.size);
		if (*(unsigned int *)&chunk.ID == 0x61746164)
			break;
		//skip chunk data bytes
		hf.seekg(chunk.size, ios::cur);
	}
	chunk_size = chunk.size;

	//get Number of samples
	int sample_size = header.bitsPerSample / 8;
	int samples_count = chunk_size * 8 / header.bitsPerSample;

	//Writing audio data
	outFile.write(reinterpret_cast<char*>(&header), sizeof(wav_header_t));
	outFile.write(reinterpret_cast<char*>(&chunk), sizeof(chunk_t));
	int num = 0, idx = 0;
	short int value[READSIZE];
	while (1){
		for (idx = 0; idx < READSIZE && !inFile.eof(); idx++){
			inFile >> value[idx];			
		}
		for (int i = 0; i < idx; i++){
			outFile.write(reinterpret_cast<char*>(&value[i]), sizeof(short int));
		}
		num += idx;
		if (inFile.eof()){
			break;
		}
	}
	samples_count = num;

	//Renew number of samples
	header.chunkSize = samples_count * 2 + 36;
	chunk.size = samples_count * 2;
	outFile.seekp(0, ios::beg);
	outFile.write(reinterpret_cast<char*>(&header), sizeof(wav_header_t));
	outFile.write(reinterpret_cast<char*>(&chunk), sizeof(chunk_t));

	hf.close();
	inFile.close();
	outFile.close();
}
