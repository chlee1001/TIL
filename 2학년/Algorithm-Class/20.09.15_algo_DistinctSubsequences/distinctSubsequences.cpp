#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int subSequences(int matrix[][100], char inputWord[100], char compareWord[100])
{
	int inputWordLen = strlen(inputWord);
	int compareWordLen = strlen(compareWord);


	if (compareWord[0] == inputWord[0]) {
		matrix[0][0] = 1;
	}
	else {
		matrix[0][0] = 0;
	}


	for (int i = 0; i < compareWordLen; i++) {
		for (int j = 1; j < inputWordLen; j++) {
			matrix[i][j] = matrix[i][j - 1];

			if (compareWord[i] == inputWord[j]) {
				if (i == 0) {
					matrix[i][j] += 1;
				}
				else {
					matrix[i][j] += matrix[i - 1][j - 1];
				}
			}

		}
	}

	/* 테이블 출력
	for (int i = 0; i < compareWordLen; i++) {
		for (int j = 0; j < inputWordLen; j++) {

			printf("%d ", matrix[i][j]);
		}
		printf("\n");
	}*/

	int cnt = matrix[compareWordLen - 1][inputWordLen - 1];

	return cnt;
}


int main()
{
	int numofData = 0;
	char* inputWord, * compareWord;
	int matrix[100][100] = { 0, };

	inputWord = (char*)malloc(10000);
	compareWord = (char*)malloc(100);

	FILE* fp;
	fp = fopen("Distinct_Subsequences.txt", "r");
	if (fp == NULL) {
		printf("Could not open Distinct_Subsequences.txt!\n");
		exit(1);
	}

	fscanf(fp, "%d", &numofData);

	for (int i = 0; i < numofData; i++) {
		fscanf(fp, "%s %s", inputWord, compareWord);
		printf("%s : %s = %d\n", inputWord, compareWord, subSequences(matrix, inputWord, compareWord));
	}

	return 0;
}