#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 1024

struct elephant {
	int weight;
	int iq;
	int index;
}Elephant[MAX];

/* 파일 입력 */
int fileLoad()
{
	FILE* fp;
	fp = fopen("smartElephant.txt", "r");
	if (fp == NULL) {
		printf("Could not open smartElephant.txt!\n");
		exit(1);
	}

	int cnt = 0;

	while (feof(fp) == 0) {
		fscanf(fp, "%d %d", &Elephant[cnt].weight, &Elephant[cnt].iq);
		Elephant[cnt].index = cnt + 1;

		cnt++;
	}
	fclose(fp);


	return cnt;
}


void sort(elephant Elephant[], int size)
{
	struct elephant temp;
	int pivot;
	int i, j;

	if (size <= 1) return; // 구간값이 1이하이면 sort가 완료된 것 이므로 return

	pivot = Elephant[size - 1].weight; // 구간의 가장 우측값을 pivot으로 정함
	i = 0; j = size - 1;

	while (i < j) {
		while (Elephant[i].weight < pivot) {
			i++;
		}

		while (Elephant[j].weight >= pivot) {
			j--;
		}

		if (i < j) {
			temp = Elephant[i];
			Elephant[i] = Elephant[j];
			Elephant[j] = temp;
		}
	}

	temp = Elephant[i];
	Elephant[i] = Elephant[size - 1];
	Elephant[size - 1] = temp;

	sort(Elephant, i); // 좌측 소구간에 대한 퀵 정렬 재귀 호출
	sort(Elephant + i + 1, size - i - 1); // 우측 소구간에 대한 퀵 정렬 재귀 호출
}


/* 결과 출력 */
void print_lds(elephant* elephant, int* path, int seq)
{
	if (path[seq] >= 0) {
		print_lds(elephant, path, path[seq]);
	}
	printf("%d\n", elephant[seq].index);

}

int main()
{
	int index = fileLoad();

	puts("** Input **");
	for (int i = 0; i < index; i++) {
		printf("%d %d\n", Elephant[i].weight, Elephant[i].iq);
	}
	puts("");

	sort(Elephant, index); // quickSort

	int dp[MAX] = { 0, };
	int path[MAX];
	int max = 0;
	int max_seq = 0;

	for (int i = 0; i < index; i++) {
		for (int j = 0; j < i; j++) {
			if ((dp[i] <= dp[j]) && (Elephant[j].weight < Elephant[i].weight) && (Elephant[j].iq > Elephant[i].iq)) {
				dp[i] = dp[j] + 1;
				path[i] = j;

				if (dp[i] > max) {
					max = dp[i];
					max_seq = i;
				}
			}
		}
	}


	puts("** Output **");
	printf("%d\n", max + 1);
	puts("");

	print_lds(Elephant, path, max_seq);
	puts("");

	return 0;
}

// Input 1
//**Input**
//6008 1300
//6000 2100
//500 2000
//1000 4000
//1100 3000
//6000 2000
//8000 1400
//6000 1200
//2000 1900
//
//* *Output * *
//4
//
//4
//5
//9
//8

// Input 2
//** Input**
//6000 2100
//1000 4000
//8000 1400
//2000 1900
//6008 1300
//500 2000
//
//* *Output * *
//3
//
//6
//4
//5

// Input3
//** Input**
//6008 1300
//6000 2100
//500 2000
//1000 3500
//1100 4000
//8000 1400
//3000 1500
//2000 1900
//
//* *Output * *
//4
//
//3
//8
//7
//1

// Input4
//** Input**
//100 900
//200 100
//300 800
//400 700
//500 600
//600 600
//
//* *Output * *
//4
//
//1
//3
//4
//5

