#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

struct path
{
	int r;
	int c;
}pos[100];

int rows = 0, cols = 0;
int* mat = 0, * costM = 0;

int main()
{
	int temp = 0;

	/* Load File */
	FILE* fp;
	fp = fopen("theCheapestWay.txt", "r");
	if (fp == NULL) { // Check availiable file
		printf("Could not open theCheapestWay.txt!\n");
		exit(1);
	}
	while (feof(fp) == 0) {
		fscanf(fp, "%d %d", &rows, &cols);
		mat = (int*)malloc(rows * cols * sizeof(int*));
		costM = (int*)malloc(rows * cols * sizeof(int*));

		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				fscanf(fp, "%d", (mat + i * cols + j));
				printf("%d ", *(mat + i * cols + j));
			}
			printf("\n");
		}


		int arr[3] = { 99 };
		int min = INT_MAX;

		for (int j = 0; j < cols; j++) { // column 별로 가중치 더해주기..
			if (j == 0) {
				for (int i = 0; i < rows; i++) {
					*(costM + i * cols + j) = *(mat + i * cols + j);
				}
			}
			else {
				for (int i = 0; i < rows; i++) {
					min = INT_MAX;
					if (i == 0) {
						for (int k = 0; k < 3; k++) {
							if (k == 2) {
								arr[k] = *(costM + (rows - 1) * cols + j - 1) + *(mat + i * cols + j);
							}
							else {
								arr[k] = *(costM + (i + 1 - k) * cols + j - 1) + *(mat + i * cols + j);
							}
							if (min > arr[k]) {
								min = arr[k];
							}
						}
						*(costM + i * cols + j) = min;
					}
					else if (i == rows - 1) {
						for (int k = 0; k < 3; k++) {
							if (k == 0) {
								arr[k] = *(costM + (0) * cols + j - 1) + *(mat + i * cols + j);
							}
							else {
								arr[k] = *(costM + (i + 1 - k) * cols + j - 1) + *(mat + i * cols + j);
							}
							if (min > arr[k]) {
								min = arr[k];
							}
						}
						*(costM + i * cols + j) = min;
					}
					else {
						for (int k = 0; k < 3; k++) {
							arr[k] = *(costM + (i + 1 - k) * cols + j - 1) + *(mat + i * cols + j);
							if (min > arr[k]) {
								min = arr[k];
							}
						}
						*(costM + i * cols + j) = min;

					}
				}
			}
		}

		int cost = INT_MAX;
		int best_rPos = 0;
		for (int i = 0; i < rows; i++) {
			if (cost > * (costM + i * cols + cols - 1)) {
				cost = *(costM + i * cols + cols - 1);
				best_rPos = i;
			}
		}

		for (int i = 0; i < cols; i++) {
			if (i == 0) {
				pos[i].r = best_rPos;
				pos[i].c = cols - 1;
			}
			else {
				min = INT_MAX;
				int min_r = INT_MAX;
				arr[0] = *(costM + best_rPos * cols + cols - 1 - i);
				arr[1] = *(costM + (best_rPos - 1 + rows) % rows * cols + cols - 1 - i);
				arr[2] = *(costM + (best_rPos + 1) % rows * cols + cols - 1 - i);
				for (int j = 0; j < 3; j++) {
					if (min > arr[j]) {
						min = arr[j];
						min_r = j;
					}
				}
				if (min_r == 1)
					best_rPos = (best_rPos - 1 + rows) % rows;
				else if (min_r == 2)
					best_rPos = (best_rPos + 1) % rows;
				pos[i].r = best_rPos;
				pos[i].c = cols - 1 - i;
			}
		}


		/* Result */
		puts("\nResult");
		for (int i = cols-1; i >= 0; i--) {
			printf("%d ", *(mat + pos[i].r * cols + pos[i].c));
		}
		printf("\n%d\n", cost);
		printf("--------------------------\n");
		free(mat);
		free(costM);
	}
	return 0;
}