#include <iostream>
#include <vector>
using namespace std;

int main() {

	vector<int> daysOfMonth = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	int T;
	cin >> T;
	string S;
	for (int i = 0; i < T; i++) {
		cin >> S;
		int month = atoi(S.substr(4, 2).c_str());
		int day = atoi(S.substr(6).c_str());
		cout << "#" << i + 1 << " ";
		if ((1 <= month && month << 12) && (1 <= day && day <= daysOfMonth[month - 1])) {
			cout << S.substr(0, 4) << "/" << S.substr(4, 2) << "/" << S.substr(6) << endl;
		}
		else {
			cout << -1 << endl;
		}

	}
	return 0;
}