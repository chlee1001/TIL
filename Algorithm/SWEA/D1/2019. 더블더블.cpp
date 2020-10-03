#include <iostream>

using namespace std;

int main() {
	int N;
	cin >> N;

	int result = 1;

	for (int i = 0; i <= N; i++) {
		cout << result << " ";
		result = result * 2;
	}
	return 0;
}