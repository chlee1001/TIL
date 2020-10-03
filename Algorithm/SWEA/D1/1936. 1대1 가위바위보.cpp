#include <iostream>

using namespace std;

int main() {
	int a, b;
	cin >> a >> b;
	//1<2,1>3, 2>1,2<3, 3<1,3>2
	if (a - b == -1 || a - b == -2) cout << "B" << endl;
	else cout << "A" << endl;

	return 0;
}