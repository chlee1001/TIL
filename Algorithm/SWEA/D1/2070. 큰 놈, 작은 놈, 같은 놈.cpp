#include <iostream>
using namespace std;

int main()
{
	int T, a,b;
	cin >> T;
	for (int i = 0; i < T; i++) {
		cin >> a >> b;
		char res = '=';
		if (a > b) res = '>';
		else if (a < b) res = '<';

		cout << "#" << i + 1 << " " << res << endl;
	}

	return 0;
}