#include <iostream>

using namespace std;

int main() {
	int T;
	cin >> T;

	int a, b;
	int div, rem;
	for (int i = 0; i < T; i++) {
		cin >> a >> b;
		div = a / b;
		rem = a % b;
		cout << "#" << i + 1 << " " << div << " " << rem << endl;
	}
	return 0;
}