#include <iostream>

using namespace std;

int main() {
	int T, N;
	cin >> T;

	int p[10][10];
	for (int i = 0; i < T; i++) {
		cin >> N;
		cout << "#" << i + 1 << endl;

		for (int j = 0; j < N; j++) {
			for (int k = 0; k <= j; k++) {
				if (k == 0 || k == j) p[j][k] = 1;
				else p[j][k] = p[j - 1][k - 1] + p[j - 1][k];
				cout << p[j][k] << " ";
			}
			cout << endl;
		}

	}
	return 0;

}