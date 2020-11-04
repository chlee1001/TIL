#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

using namespace std;

struct Dress
{
	int id, T, S; // T: day, S: penalty
	float Worth;
}dress[1001];


int main()
{
	int testCase, N, T;

	/* Load File */
	FILE* fp;
	fp = fopen("dressmaker.txt", "r");
	if (fp == NULL) { // Check availiable file
		printf("Could not open dressmaker.txt!\n");
		exit(1);
	}

	fscanf(fp, "%d", &testCase); // TestCase
	for (int j = 0; j < testCase; j++) {
		fscanf(fp, "%d", &N); // Orders
		for (int i = 0; i < N; i++) {
			fscanf(fp, "%d %d", &dress[i].T, &dress[i].S);
			dress[i].Worth = (float)dress[i].T / dress[i].S;
			dress[i].id = i;
		}

		Dress temp;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N - 1; j++) {
				if (dress[j].Worth > dress[j + 1].Worth) {
					temp = dress[j];
					dress[j] = dress[j + 1];
					dress[j + 1] = temp;
				}
			}
		}

		for (int i = 0; i < N; i++) {
			printf("%d ", dress[i].id + 1);
		}
		puts("");

	}
	fclose(fp);
	return 0;

}