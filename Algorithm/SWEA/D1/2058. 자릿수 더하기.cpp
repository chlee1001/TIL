#include <iostream>
using namespace std;

int main() {
	int N;
	cin >> N;

	int a, sum = 0;
	for (int i = 0; i < 4; i++) {
		a = N % 10;
		N = N / 10;
		sum += a;
	}

	cout << sum << endl;
	return 0;
}