#include <iostream>

using namespace std;

int* extendedEuclid(int a, int b)
{
	int* xyd = (int*)malloc(sizeof(int) * 3);

	if (b == 0) {
		xyd[2] = a; // d
		xyd[0] = 1; // x
		xyd[1] = 0; // y

		return xyd;
	}
	else {
		int t1, t2;
		xyd = extendedEuclid(b, a % b);
		t1 = xyd[0];
		t2 = xyd[1];
		xyd[0] = xyd[1];
		xyd[1] = t1 - a / b * t2;

		return xyd;
	}

	free(xyd);
}

int main()
{
	int a, b;
	cin >> a >> b;

	int* XYD = extendedEuclid(a, b);

	cout << XYD[0] << " " << XYD[1] << " " << XYD[2] << endl;

	return 0;
}