#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MIN(a,b)  (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))


int main()
{
	int f; // number of existing health centers
	int is; // number of intersections

	/* Load File */
	FILE* fp;
	fp = fopen("firestation.txt", "r");
	if (fp == NULL) { // Check availiable file
		printf("Could not open firestation.txt!\n");
		exit(1);
	}

	int cost[101][101]; // cost Matrix

	while (feof(fp) == 0) {
		fscanf(fp, "%d %d", &f, &is);


		int u, v, c;
		int dis[501], vis[501];

		/* Initialize  */
		// inf = 9999
		for (int i = 1; i <= is; i++) {
			dis[i] = 9999; vis[i] = 0;
			for (int j = 1; j <= is; j++) {
				if ( i == j) cost[i][j] = 0;
				else cost[i][j] = 9999;
			}
			
		}

		// Check the current fire station location
		for (int i = 1; i <= f; i++) {
			fscanf(fp, "%d", &u);
			dis[u] = 0;
			vis[u] = 1;
		}

		// Input cost in matrix
		for (int i = 1; i <= is; i++) {
			fscanf(fp, "%d %d %d", &u, &v, &c);
			cost[u][v] = cost[v][u] = c;
		}


		// Floyd-warshall algorithm
		for (int k = 1; k <= is; k++) {
			for (int i = 1; i <= is; i++) {
				for (int j = 1; j <= is; j++) {
					cost[i][j] = MIN(cost[i][j], cost[i][k] + cost[k][j]);
				}
			}
		}


		for (int i = 1; i <= is; i++) {
			if (vis[i])
				for (int j = 1; j <= is; j++) {
					dis[j] = MIN(dis[j], cost[i][j]);
				}

		}

		//// show matrix
		//for (int i = 1; i <= is; i++) {
		//	for (int j = 1; j <= is; j++) {
		//		printf("%d ", cost[i][j]);
		//	}
		//	puts("");
		//}

		int ans = 9999, pos = 0;

		// find lowest intersection number 
		for (int i = 1; i <= is; i++) {
			int temp = -1;
			for (int j = 1; j <= is; j++)
				temp = MAX(temp, MIN(dis[j], cost[i][j]));
			if (ans > temp)ans = temp, pos = i;
		}
		printf("\n%d\n", pos);
	}

	fclose(fp);

	return 0;
}