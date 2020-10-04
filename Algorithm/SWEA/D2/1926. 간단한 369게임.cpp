#include <iostream>

using namespace std;

int count369(int n) {
	int count = 0;
	while (true) {
		int remain = n % 10;
		if (remain == 3 || remain == 6 || remain == 9) count++;
		n /= 10;
		if (n == 0)break;
	}
	return count;
}

int main() {
	int N;
	cin >> N;

	for (int i = 1; i <= N; i++) {
		int cnt = count369(i);

		if (cnt == 0) {
			cout << i << " ";
			continue;
		}

		for (int j = 0; j < cnt; j++) {
			cout << "-";

		}
		cout << " ";

	}
	return 0;
}