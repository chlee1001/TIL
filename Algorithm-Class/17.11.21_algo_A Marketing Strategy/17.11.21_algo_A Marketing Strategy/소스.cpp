#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct
{
	int x;
	int y;
} XY;

double ClosestPair(XY* pair, int left, int right, int n);
double calDistance(XY* a, XY* b);
double minNum(double a, double b);
int compare(const void* a, const void* b);

int N; // Data Set ����
double min = -1; // �ֱ����� �Ÿ�

int main(void)
{
	XY* pair = NULL; // ��ǥ ����
	FILE *fp;

	fp = fopen("marketing_strategy.txt", "r");
	if (fp == NULL) { // Check availiable file
		printf("Could not open marketing_strategy.txt!\n");
		exit(1);
	}

	/* ��ǥ ���� �Է� */
	fscanf(fp, "%d", &N);

	/* ��ǥ �Է� */
	pair = (XY*)malloc(sizeof(XY)*N);
	for (int i = 0; i < N; i++) {
		fscanf(fp, "%d %d", &(pair + i)->x, &(pair + i)->y);
	}

	fclose(fp);

	/* ������ */
	qsort(pair, (size_t)N, sizeof(XY), compare);

	/* ��� ��� */
	printf("<Data Set>\n");
	for (int i = 0; i < N; i++) {
		printf("(%d, %d)\n", (pair + i)->x, (pair + i)->y);
	}

	printf("\nResult: %.2lf\n", ClosestPair(pair, 0, N - 1, N));

	free(pair);

	return 0;
}

double ClosestPair(XY* pair, int left, int right, int n)
{
	if (n == 2) { // Brute-Force-CPair
		return calDistance(pair + left, pair + right);
	}

	else if (n == 3) { // Brute-Force-Cpair
		double distance1, distance2, distance3, min;
		distance1 = calDistance(pair, pair + 1);
		distance2 = calDistance(pair + 1, pair + 2);
		distance3 = calDistance(pair + 2, pair);

		/* �ּҰ� ã�� */
		min = minNum(distance1, distance2);
		min = minNum(distance3, min);
		return min;
	}

	else {
		int mid = (left + right) / 2;

		double distance;
		double dLeft, dRight;

		dLeft = ClosestPair(pair, left, mid, mid - left + 1);
		dRight = ClosestPair(pair, mid + 1, right, right - mid);
		distance = minNum(dLeft, dRight);

		XY* pairTemp = (XY*)malloc(sizeof(XY)*n);
		int cnt = 0;

		for (int i = left; i <= right; i++) { // �� distance�� ���� �� ��ǥ ����
			if (abs((pair + i)->x - (pair + mid)->x) < distance) {
				(pairTemp + cnt)->x = (pair + i)->x;
				(pairTemp + cnt)->y = (pair + i)->y;
				cnt++;
			}
		}

		double minSub = -1; // ���� ��ǥ�� �ּ� ��

		/* ���� ��ǥ ���� �Ÿ��� �� distance �� */
		for (int i = 0; i < cnt; i++) {
			for (int j = i + 1; j < cnt; j++) {

				/* ���� ��ǥ ���� �Ÿ� ���ϱ�*/
				minSub = calDistance(pairTemp + i, pairTemp + j);

				if (minSub < distance) { //  ���� ��ǥ���� �Ÿ� < distance �̸� distance ���� 
					distance = minSub;
				}
			}
		}

		free(pairTemp);

		return distance;
	}
}

/* �Ÿ� ��� �Լ� */
double calDistance(XY* a, XY* b)
{
	double distance = sqrt(pow(a->x - b->x, 2) + pow(a->y - b->y, 2));

	return distance;
}

/* ���� ���� ã�� �Լ�*/
double minNum(double a, double b)
{
	if (a < b) {
		return a;
	}
	else {
		return b;
	}
}


/* �������� ���� �� �Լ� */
int compare(const void* a, const void* b)
{
	if (((const XY*)a)->x > ((const XY*)b)->x) {
		return 1;
	}
	else if (((const XY*)a)->x == ((const XY*)b)->x) {
		return 0;
	}
	else {
		return -1;
	}
}

/*

@Problem 15 : A marketing Strategy
A telephone company seeks to claim they provide high-speed broadband access to customers. It will suffice for marketing purposes if they can create just one such link directly connecting two locations.
As the cost for installing such a pair of locations are the shortest distance apart so as to provide the cheapest possible implementation of this marketing strategy.
More precisely, given a set of points in the plane, find the distance between the closest pair of points provided this distance is less than some limit.
If the closest pair is too far apart, marketing will have to opt for some less expensive strategy.

@Input
The input set starts with an integer N(0 �� N�� 30), which denotes the number of points in this set.
The next N lines contain the coordinates of N two-dimensional points.
The two numbers denote the x- and y- coordinates of N two-dimensional points.
The two numbers denote the x- and y-coordinates, respectively.
The input is terminated by a set whose N =0, which should not be processed.
All coordinates will have values less than 40,000 and be non-negative.

@Output
For each input set, produce a single line of output containing a floating point number (with two digit after the decimal point) which denotes the distance between the closest two points.
If there do not exit two points whose distance is less than 10,000, print the line ��Infinity��.

@Sample Input
5
0 2
6 67
39 107
43 71
189 140

@Sample Output
36.22

*/