#define PI 3.1415926535
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

struct YX {
	double y;
	double x;
	int flag = 0;
}coord[100], setCoord[100];


// Compute angle But, x y ==> y x
double computeAngle(YX aPoint, YX bPoint)
{
	double dx, dy;
	double angle;
	dy = bPoint.x - aPoint.x;
	dx = bPoint.y - aPoint.y;

	if (dx >= 0 && dy == 0) angle = 0;
	else {
		angle = abs(dy) / (abs(dx) + abs(dy));
		if (dx < 0 && dy >= 0) angle = 2 - angle;
		else if (dx <= 0 && dy < 0) angle = 2 + angle;
		else if (dx > 0 && dy < 0) angle = 4 - angle;
	}

	return angle * 90;

}

// Calculate Distance between two coordinate
double getDistance(YX p1, YX p2)
{
	return sqrt(pow((p1.x - p2.x), 2) + pow((p1.y - p2.y), 2));
}


int main()
{
	ifstream readFile;
	int numCase; // number of case
	int frosh; // number of frosh

	readFile.open("cleanCampus.txt");
	if (readFile.fail()) {
		cout << "Failed to open file." << endl;
		return 0;
	}
	else {
		readFile >> numCase;

		while (numCase > 0) {
			readFile >> frosh;
			cout << "Input" << endl;
			for (int i = 1; i <= frosh; i++) {
				readFile >> coord[i].y >> coord[i].x;
				cout << coord[i].y << " " << coord[i].x << endl;
			}
			numCase -= 1;
		}
	}
	readFile.close();

	// start point (0,0)
	coord[0].y = 0;
	coord[0].x = 0;

	int pos = 0;
	int flag = 0;
	int a = 0;

	while (1) {
		setCoord[a].y = coord[pos].y;
		setCoord[a].x = coord[pos].x;
		coord[pos].flag = 1;

		int changed = 0;
		double minAngle = 999;

		for (int i = 0; i < frosh; i++) {

			double angle = computeAngle(setCoord[a], coord[i + 1]);

			// Find Min angle (if the coordinate is used, then pass)
			if (minAngle > angle && coord[i + 1].flag == 0) {
				flag = 0;
				for (int j = 0; j <= a; j++) {
					// On the same line, Check distance and choose the longer coordinate.
					if (coord[i + 1].x == 0 || coord[i + 1].y == 0) {
						if (getDistance(setCoord[0], coord[i + 1]) >= getDistance(setCoord[0], setCoord[j])) {
							flag++;
						}
						if (flag == a + 1) {
							minAngle = angle;
							pos = i + 1;
							changed = 1;
						}
					}
					else { // On the different line,
						minAngle = angle;
						pos = i + 1;
						changed = 1;
					}
				}
			}
		}
		a += 1;
		if (changed == 0) break; // Exit when there is no more change
	}


	//for (int i = 0; i <= frosh; i++) {
	//	cout << setCoord[i].x << " " << setCoord[i].y << endl;
	//}


	double sum = 0;
	for (int i = 0; i <= frosh; i++) {
		sum += getDistance(setCoord[i], setCoord[i + 1]);
	}
	sum += 2; // tied X2

	cout << fixed;
	cout.precision(2);
	cout << "result: " << sum << endl;

	return 0;
}