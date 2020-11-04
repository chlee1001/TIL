#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

int stack[30] = { 0, };
int task[100] = { 0, };
int flipPos = 0; // To save the flip position as a process
int cntFlip = 0; // To output the flip position

 
int getMaxPos(int pan_stack[], int length) // Return max value's position
{
	int max = stack[0], pos = 0;
	for (int i = 0; i <= length; i++) {
		if (max < pan_stack[i]) {
			max = pan_stack[i];
			pos = i;
		}
	}
	return pos;
}

void flip(int pan_stack[], int length, int pos) // FLIP!!
{
	int set = length - pos;
	for (int i = 0, j = set; i < (set + 1) / 2; i++, j--) {
		int temp = pan_stack[i];
		pan_stack[i] = pan_stack[j];
		pan_stack[j] = temp;
	}
	task[flipPos++] = pos;
	cntFlip++; 
}

int sort_check(int pan_stack[], int length) // Check the array whether it is sorted
{
	for (int i = 0; i < length - 1; i++) {
		if (pan_stack[i] > pan_stack[i + 1]) {
			return 0; // not sorted
		}
	}
	return 1; // sorted
}

int main()
{
	FILE* fp;

	fp = fopen("pancakes.txt", "r");
	if (fp == NULL) { // Check availiable file
		printf("Could not open pancakes.txt!\n");
		exit(1);
	}

	int length = 0; // number of pancakes

	/* Load the file and store on array */
	while (feof(fp) == 0) {
		fscanf(fp, "%d", &stack[length]);
		length++;
	}
	fclose(fp);


	/* Print Input Data */
	for (int i = 0; i < length; i++) {
		printf("%d ", stack[i]);
	}


	/* Sorting */
	for (int i = length - 1; i > 0; i--) {
		int maxPos = getMaxPos(stack, i); // find max value's position
		if (sort_check(stack, length)) { // Checking whether sorted
			break;
		}
		else {
			if (stack[0] == stack[maxPos]) { // When the maximum is at the forefront
				flip(stack, length, length - i);
			}
			else if ((stack[i] == stack[maxPos])) { // 최대값이 올바른 위치...맨 아래..등등에 잘 있을 경우
				continue;
			}
			else {
				flip(stack, length, length - maxPos); // Move the maximum to the front
				flip(stack, length, length - i);
			}
		}
	}

	printf("(");
	for (int i = 0; i < length; i++) {
		printf("%d ", stack[i]);
	}
	printf(")\n");

	for (int i = 0; i <= cntFlip; i++) {
		printf("%d ", task[i]);
	}

	return 0;
}