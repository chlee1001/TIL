#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main()
{
	ifstream readFile;
	int f; // number of existing health centers
	int is; // number of intersections

	readFile.open("healthCenter.txt");
	if (readFile.fail()) {
		cout << "Failed to open file." << endl;
		return 1;
	}
	else {
		readFile >> f >> is;
		int u, v, c;

		int dis[501], vis[501];
		vector<vector<int> > cost(is + 1, vector<int>(is + 1));


		for (int i = 1; i <= is; i++) {
			dis[i] = 9999; vis[i] = 0;
			for (int j = 1; j <= is; j++)
				cost[i][j] = i == j ? 0 : 9999;
		}

		for (int i = 1; i <= f; i++) {
			readFile >> u;
			dis[u] = 0;
			vis[u] = 1;
		}

		for (int i = 1; i <= is; i++) {
			readFile >> u >> v >> c;
			cost[u][v] = cost[v][u] = c;
		}


		for (int k = 1; k <= is; k++) {
			for (int i = 1; i <= is; i++) {
				for (int j = 1; j <= is; j++) {
					cost[i][j] = min(cost[i][j], cost[i][k] + cost[k][j]);
				}
			}
		}

		for (int i = 1; i <= is; i++) {
			if (vis[i])
				for (int j = 1; j <= is; j++)
					dis[j] = min(dis[j], cost[i][j]);
		}

		int ans = 9999, pos = 0;

		for (int i = 1; i <= is; i++) {
			int temp = -1;
			for (int j = 1; j <= is; j++)
				temp = max(temp, min(dis[j], cost[i][j]));
			if (ans > temp)ans = temp, pos = i;
		}
		cout << pos << endl;
	}

	readFile.close();

	return 0;
}