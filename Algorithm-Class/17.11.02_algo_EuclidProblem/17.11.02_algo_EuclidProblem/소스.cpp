#include <stdio.h>
#include <stdlib.h>

/* initialize */
int mod(int a, int b); // for 'mod'
int *extendedEuclid(int a, int b); // caculate extendedEuclid

int main(void)
{
	int a = 0, b = 0;
	printf("Input A, B: ");
	scanf("%d %d", &a, &b);

	int *gcd = extendedEuclid(a, b);

	printf("GCD is: %d\nX is: %d\nY is: %d\n", gcd[0], gcd[1], gcd[2]);

	return 0;
}


int mod(int a, int b) {
	return a %b;
}

int *extendedEuclid(int a, int b) {
	int *dxy = (int *)malloc(sizeof(int) * 3);

	if (b == 0) {
		dxy[0] = a;
		dxy[1] = 1;
		dxy[2] = 0;

		return dxy;
	}

	else {
		int t, t2;
		dxy = extendedEuclid(b, mod(a, b));
		t = dxy[1];
		t2 = dxy[2];
		dxy[1] = dxy[2];
		dxy[2] = t - a / b *t2;

		return dxy;
	}
}
