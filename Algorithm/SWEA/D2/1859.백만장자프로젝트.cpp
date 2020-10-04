#include <iostream>

using namespace std;
int a[1000000];

int main() {
	int T, N;
	cin >> T;

	long long sum;
	int max;

	for (int i = 0; i < T; i++) {
		cin >> N;
		for (int j = 0; j < N; j++) {
			cin >> a[j];
		}
		sum = 0;
		max = a[N - 1];
		for (int j = N - 2; j >= 0; --j) {
			if (max <= a[j]) max = a[j];
			else sum += (max - a[j]);
		}
		cout << "#" << i + 1 << " " << sum << endl;
	}
	return 0;
}