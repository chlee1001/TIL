#include <iostream>
#include <stdlib.h>

#define MIN(a,b) (a<b ? a:b)

using namespace std;

struct coordinate
{
	int x;
	int y;
};

/* Compare Function for Quick sort */
int compare(const void* a, const void* b)
{
	if (((const coordinate*)a)->x > ((const coordinate*)b)->x)	return 1;
	else if (((const coordinate*)a)->x == ((const coordinate*)b)->x)return 0;
	else return -1;
}

/* Fuction of Return calculated distance  */
double getDistance(coordinate* a, coordinate* b)
{
	double distance = sqrt(pow(a->x - b->x, 2) + pow(a->y - b->y, 2));
	return distance;
}

double ClosestPair(coordinate* XY, int left, int right, int n)
{
	if (n == 2) { // Brute-Force-CPair
		return getDistance(XY + left, XY + right);
	}

	else if (n == 3) { // Brute-Force-Cpair
		double distance1, distance2, distance3, min;
		distance1 = getDistance(XY, XY + 1);
		distance2 = getDistance(XY + 1, XY + 2);
		distance3 = getDistance(XY + 2, XY);

		/* Find Min */
		double temp = MIN(distance1, distance2);
		min = MIN(distance3, temp);
		return min;
	}
	else {
		int mid = (left + right) / 2;

		double distance;
		double dLeft, dRight;

		dLeft = ClosestPair(XY, left, mid, mid - left + 1);
		dRight = ClosestPair(XY, mid + 1, right, right - mid);
		distance = MIN(dLeft, dRight);

		coordinate* xyTemp = (coordinate*)malloc(sizeof(coordinate) * n);
		
		int cnt = 0;
		for (int i = left; i <= right; i++) { // distance에 포함 된 자표 저장
			if (abs((XY + i)->x - (XY + mid)->x) < distance) {
				(xyTemp + cnt)->x = (XY + i)->x;
				(xyTemp + cnt)->y = (XY + i)->y;
				cnt++;
			}
		}

		double minSub = -1; // 세부 좌표의 최소 값

		/* Compare between 세부 좌표 간의 거리와 distance */
		for (int i = 0; i < cnt; i++) {
			for (int j = i + 1; j < cnt; j++) {

				/* calculate distance  between 세부 좌표 간*/
				minSub = getDistance(xyTemp + i, xyTemp + j);

				if (minSub < distance) { //  세부 좌표간의 거리 < distance: distance 갱신 
					distance = minSub;
				}
			}
		}

		free(xyTemp);

		return distance;
	}
}


int main()
{
	int N = 0;
	coordinate* XY = NULL;

	cout << "Input N: ";
	cin >> N;
	while (N != 0) {
		XY = (coordinate*)malloc(sizeof(coordinate) * N); // Init XY with N

		/* Input coordinate */
		cout << "Input X Y:\n";
		for (int i = 0; i < N; i++) {
			cin >> (XY + i)->x >> (XY + i)->y;
		}
		for (int i = 0; i < N; i++) {
			if ((XY + i)->x >= 10000 || (XY + i)->y >= 10000) {
				cout << "Result: Infinity" << endl;
				return 0;
			}
		}
		

		/* Quick Sort */
		qsort(XY, (size_t)N, sizeof(coordinate), compare);


		cout << fixed;
		cout.precision(2);
		cout << "Result: " << ClosestPair(XY, 0, N - 1, N) << endl;

		cout << "Input N: ";
		cin >> N;
	}
	free(XY);

	return 0;
}