#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int subSequences(int matrix[][100], char inputWord[100], char compareWord[100])
{
	int inputWordLen = strlen(inputWord); // length of inputWord
	int compareWordLen = strlen(compareWord); // length of compareWord


	// Compare the first spelling of two words - Because there is no previous level value
	if (compareWord[0] == inputWord[0]) {
		matrix[0][0] = 1;
	}
	else {
		matrix[0][0] = 0;
	}

	// Compare the spelling of two words -
	for (int i = 0; i < compareWordLen; i++) {
		for (int j = 1; j < inputWordLen; j++) {
			matrix[i][j] = matrix[i][j - 1];

			if (compareWord[i] == inputWord[j]) {
				if (i == 0) { // In the first line, if they are the same, add 1.
					matrix[i][j] += 1;
				}
				else { // In the other line, add the value at 11 o'clock.
					matrix[i][j] += matrix[i - 1][j - 1];
				}
			}

		}
	}

	/* Print Table - for Check Matrix */
	/*for (int i = 0; i < compareWordLen; i++) {
		for (int j = 0; j < inputWordLen; j++) {

			printf("%d ", matrix[i][j]);
		}
		printf("\n");
	}*/

	// Result that weighted value
	int result = matrix[compareWordLen - 1][inputWordLen - 1];

	return result;
}

/* Function for check whether uppercase */
int upperCheck(char* word)
{
	int check = 0;
	for (int j = 0; j < strlen(word); j++) {
		if (!islower(word[j])) return 1; // If there is a uppercase, return 1
	}
	return 0; // no uppercase, return 0
}

int main()
{
	int numofData = 0;
	char* inputWord, * compareWord;
	int matrix[100][100] = { 0, };

	inputWord = (char*)malloc(10000);
	compareWord = (char*)malloc(100);

	FILE* fp;
	fp = fopen("lab1.txt", "r");
	if (fp == NULL) {
		printf("Could not open lab1.txt!\n");
		exit(1);
	}

	fscanf(fp, "%d", &numofData); // number of input data


	for (int i = 0; i < numofData; i++) {
		fscanf(fp, "%s %s", inputWord, compareWord);

		if ((strlen(inputWord) > 10) || (strlen(compareWord) > 10)) continue; // if word's length is over than 10, pass the testcase

		int checkUpper_inputWord = upperCheck(inputWord);
		int checkUpper_compareWord = upperCheck(compareWord);

		if ((checkUpper_inputWord == 0) && (checkUpper_compareWord == 0)) { // if both word don't have uppercase...
			printf("Testing %d\tInput: S = %s\n\t\t\tT = %s\n\t\tOutput: %d\n\n", i + 1, inputWord, compareWord, subSequences(matrix, inputWord, compareWord));
		}
	}

	fclose(fp);
	free(inputWord);
	free(compareWord);

	return 0;
}