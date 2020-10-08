#include<iostream>
#include<fstream>
#include<string>
#include <malloc.h>

using namespace std;

double prims(int n);
double** matrix;

int main(void)
{
	ifstream readFile;
	readFile.open("savingInk.txt");    // Open File
	if (readFile.fail()) {
		cout << "Failed to open file." << endl;
		return 1;
	}

	int vertex;
	double* xPtr;
	double* yPtr;

	if (readFile.is_open()) {
		readFile >> vertex; // Read number of Vertex


		/* Memory allocation */
		xPtr = (double*)malloc(sizeof(double) * vertex);
		yPtr = (double*)malloc(sizeof(double) * vertex);

		matrix = new double* [vertex];
		for (int i = 0; i < vertex; i++) {
			matrix[i] = new double[vertex];
		}

		/* Read X,Y */
		for (int i = 0; i < vertex; i++) {
			readFile >> xPtr[i];
			readFile >> yPtr[i];
		}

		for (int i = 0; i < vertex; i++) {
			for (int j = i; j < vertex; j++) {
				matrix[i][j] = sqrt((pow((xPtr[i] - xPtr[j]), 2)) + (pow((yPtr[i] - yPtr[j]), 2)));
				matrix[j][i] = matrix[i][j];
			}
		}

		readFile.close();
	}


	double Result = prims(vertex);
	cout.precision(3);
	cout << Result << endl;


	/* Deallocate memory */
	for (int i = 0; i < vertex; i++) {
		delete[] matrix[i];
	}
	delete[] matrix;

	return 0;
}

double prims(int n) {
	double result = 0.0;
	int current = 0;
	int next = -1;
	double min = 0;

	double* distanceW = (double*)malloc(sizeof(double) * n);

	for (int i = 0; i < n; i++) {
		distanceW[i] = INT_MAX;
	}

	for (int i = 1; i < n; i++) {
		distanceW[current] = -1;
		min = INT_MAX;
		for (int j = 0; j < n; j++) {
			if (current != j && distanceW[j] > 0) {
				if (distanceW[j] > matrix[current][j]) {
					distanceW[j] = matrix[current][j];
				}

				if (distanceW[j] < min) {
					min = distanceW[j];
					next = j;
				}
			}
		}
		result += min;
		current = next;
	}

	return result;
}

