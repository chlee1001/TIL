#include <iostream>

using namespace std;

int main() {
	string s;
	cin >> s;
	for (int i = 0; i < s.length(); i++) {
		cout << s.at(i) - 64 << " ";
	}
	return 0;
}