#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int cal(int* money, int sum, int people)
{
	int avg;
	int mod;
	int cost = 0;

	avg = sum / people;
	mod = sum / 10 % people;

	/* Sort Descending */
	for (int i = 0; i < people; i++) {
		for (int j = 0; j < people - 1; j++) {
			if (money[i] > money[j]) {
				money[i] ^= money[j];
				money[j] ^= money[i];
				money[i] ^= money[j];
			}
		}
	}

	int remain = 0;
	for (int i = 0; i < people; i++) {

		if (i < mod)
			remain = 10;
		else
			remain = 0;

		cost += abs(money[i] - (avg + remain));
	}

	return cost / 2;
}

int main()
{
	FILE* fp;
	fp = fopen("thanksgivingTrip.txt", "r");

	if (fp == NULL) { // Check availiable file
		printf("Could not open thanksgivingTrip.txt!\n");
		exit(1);
	}

	int people = 0;
	int* money;
	int sum = 0;

	while (feof(fp) == 0)
	{
		fscanf(fp, "%d", &people);

		if (people == 0)
			break;

		sum = 0;
		money = (int*)malloc(sizeof(int) * people);

		for (int i = 0; i < people; i++) {
			fscanf(fp, "%d", &money[i]);
			sum += money[i];
		}

		printf("\\%d\n", cal(money, sum, people));
		free(money);
	}
	fclose(fp);

}