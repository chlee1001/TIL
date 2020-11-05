#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>

int fibo_arr[50];

int fibo_dynamicP(int n) {

    if (fibo_arr[n] != 0)
        return fibo_arr[n];
    if (n < 2)
        fibo_arr[n] = n;
    else
        fibo_arr[n] = fibo_dynamicP(n - 1) + fibo_dynamicP(n - 2);

    return fibo_arr[n];
}
int fibo_refunc(int n)
{
    if (n < 2)
        return n;
    return fibo_refunc(n - 1) + fibo_refunc(n - 2);
}

int main(void) {

    int n = 0;
    scanf("%d", &n);
    long savetime = clock();
    printf("%d\n", fibo_dynamicP(n));
    printf("fibo_dynamic : %dms\n", clock() - savetime);

    printf("%d\n", fibo_refunc(n));
    printf("fibo_refunc : %dms\n", clock() - savetime);
    return 0;
}