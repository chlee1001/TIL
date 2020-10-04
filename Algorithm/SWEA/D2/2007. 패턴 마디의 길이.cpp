#include <iostream>

using namespace std;

int main() {
	int T;
	char str[31];

	int size = 0;
	cin >> T;
	for (int i = 0; i < T; i++) {
		cin >> str;

		for (size = 2; size <= 10; size++) {
			bool repeating = true;
			for (int j = 0; j < size; j++) {
				if (str[j] != str[j + size]) {
					repeating = false;
					break;
				}
			}
			if (repeating) {
				cout << "#" << i + 1 << " " << size << endl;
				break;
			}
		}
	}
	return 0;

}