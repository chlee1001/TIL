#define _CRT_SECURE_NO_WARNINGS


#include<cstdio>
#include<cstring>
#include<cmath>

void print(int limit, int first, int second, int reverse);

int main()
{
	int limit = 1;
	int c1, c2, n1, n2;

	/* Load File */
	FILE* fp;
	fp = fopen("jewelBox.txt", "r");
	if (fp == NULL) { // Check availiable file
		printf("Could not open jewelBox.txt!\n");
		exit(1);
	}
	while (feof(fp) == 0) {
		fscanf(fp, "%d", &limit);
		if (limit == 0) return 0;

		fscanf(fp, "%d %d %d %d", &c1, &n1, &c2, &n2);


		if ((n1 / c1) > (n2 / c2)) print(limit, n1, n2, 0);

		else print(limit, n2, n1, 1);
	}

	fclose(fp);
	return 0;

}

void print(int limit, int first, int second, int reverse)
{
	int cnt = 0;
	int flag = 0;

	while (flag == 0) {
		if (limit % first == 0) {
			flag = 1;
			printf("%d %d\n", limit / first, cnt);
		}
		else {
			limit = limit - second;
			cnt++;
			if (limit % first == 0) {
				flag = 1;
				if (reverse == 1) printf("%d %d\n", cnt, limit / first);
				else printf("%d %d\n", limit / first, cnt);
			}
			else if (limit < 0) {
				printf("failed\n");
				flag = 1;
			}

		}
	}
}
