#include <iostream>

using namespace std;

int p, q, n, e[1000], d[1000];
long long plainText = 0, encryptText = 0, decryptText = 0;

int primeChecks(long int n)
{
	int i;
	long int j = sqrt(n);

	for (i = 2; i <= j; i++) {
		if (n % i == 0)
			return 0;
	}
	return 1;
}

int gcd(int a, int b)
{
	if (b == 0)
		return a;
	else
		return gcd(b, a % b);
}

int find_d(long int x, int sn)
{
	long int k = 1;
	while (1) {
		k += sn;
		if (k % x == 0) {
			return(k / x);
		}
	}
}

void setup()
{
	int k = 0;

	n = p * q; // 7, 17 119
	int sn = (p - 1) * (q - 1); // 96
	int j = 0;
	for (int i = 2; i < sn; i++) { // find e
		int tmp = gcd(i, sn);
		if (tmp == 1) {
			e[k] = i;
			int temp = find_d(e[k], sn); // find d
			if (e[k] > 0) {
				d[k] = temp;
				k++;
			}
			if (k == 99)
				break;
			j++;
		}
	}
}

long long modular(long long base, long long exp, int mod) {
	long long res = 1;
	while (exp > 0) {
		if (exp % 2 == 1)
			res = (res * base) % mod;
		exp = exp >> 1;
		base = (base * base) % mod;
	}
	return res;
}

void encrypt()
{
	long long a = plainText, b = e[0];
	encryptText = modular(a, b, n);
}

void decrypt()
{
	long long a = encryptText, b = d[0];
	decryptText = modular(a, b, n);
}


int main()
{
	cout << "Input two Prime number (p, q): ";
	cin >> p >> q;

	if (!primeChecks(p) || (!primeChecks(q))) {
		printf("Wrong Prime numbers\n");
		exit(0);
	}

	cout << "Input Original Message: ";
	cin >> plainText;
	setup();


	cout << "\nPublic Key" << endl << "P(e,n) = " << e[0] << ", " << n << endl;
	encrypt();
	cout << "Cipher text is " << encryptText << endl;

	cout << "\nSecret Key" << endl << "S(d,n) = " << d[0] << ", " << n << endl;
	decrypt();
	cout << "Original text is " << decryptText << endl;
}