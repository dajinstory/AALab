#include <stdio.h>
#include <iostream>
#include <string>
#include <string.h>
#include <cstdio>
#include <stdlib.h>
#include <cmath>
using namespace std;

int main() {
	FILE *fin = NULL;
	FILE *fout = NULL;
	string filename_txt = "./txt/LMS_example";
	string filetype_txt = ".txt";
	string filename_txt_s;
	char* filename_txt_c;

	string filename_binary = "./binary/LMS_example";
	string filetype_binary = ".bin";
	string filename_binary_s;
	char* filename_binary_c;

	char tmp[65] = { 0 };
	string number;
	double num;

	filename_binary_s = filename_binary + filetype_binary;
	filename_binary_c = &filename_binary_s[0u];
	fout = fopen(filename_binary_c, "w");

	//for one example
	filename_txt_s = filename_txt + filetype_txt;
	filename_txt_c = &filename_txt_s[0u];
	fin = fopen(filename_txt_c, "r");
	for (int i = 0; i < 50000; i++){
		fscanf(fin, "%lf", &num);
		fprintf(fout, "%lf", num);
	}
	fclose(fin);


	//for multi example with number orderded
	/*
	for (int i = 1; i <= 25; i++) {
	itoa(i, tmp, 10);
	number = string(tmp);
	filename_txt_s = filename_txt + number + filetype_txt;
	filename_txt_c = &filename_txt_s[0u];
	fin = fopen(filename_txt_c, "r");

	for (int i = 0; i < 200; i++){
	fscanf(fin, "%lf", &num);
	fprintf(fout, "%lf", num);

	}

	fclose(fin);
	}
	*/
	fclose(fout);
	return 0;
}