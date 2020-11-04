#include<iostream>
#include<fstream>
#include <vector>
#include <algorithm>

using namespace std;

int getParent(int set[], int x);
void unionParent(int set[], int a, int b);
bool sameParent(int parent[], int x, int y);


struct Pos {
	double x, y;
	int nodeName;
}pos[31];

class Dot { // Declare the coordinate class
public:
	int node[2];
	double distance;
	Dot(int a, int b, double distance) {
		this->node[0] = a;
		this->node[1] = b;
		this->distance = distance;
	}
	bool operator <(Dot& dot) {
		return this->distance < dot.distance;
	}
};


int main(void)
{
	ifstream readFile;
	readFile.open("savingInk.txt");    // Open File
	if (readFile.fail()) {
		cout << "Failed to open file." << endl;
		return 1;
	}

	int vertex;
	vector<Dot> d;

	if (readFile.is_open()) {
		readFile >> vertex; // Read number of Vertex

		double distance[100];
		for (int i = 0; i < vertex; i++) {
			readFile >> pos[i].x >> pos[i].y;
			pos[i].nodeName = i + 1;
		}

		int edgeCnt = 0;
		for (int i = 0; i < vertex; i++) {
			for (int j = i + 1; j < vertex; j++) {
				distance[edgeCnt] = sqrt((pow((pos[i].x - pos[j].x), 2)) + (pow((pos[i].y - pos[j].y), 2)));
				d.push_back(Dot(pos[i].nodeName, pos[j].nodeName, distance[edgeCnt]));
				edgeCnt++;
			}
		}

		sort(d.begin(), d.end()); // Sort by distance ascending

		// Location of each node ,,,, Cycle Table
		int set[30];
		for (int i = 0; i < vertex; i++) {
			set[i] = i;
		}

		double sum = 0; // Initialize the sum of distances to 0

		for (int i = 0; i < d.size(); i++) {
			// Other parents,,,, when no cycle
			if (!sameParent(set, d[i].node[0] - 1, d[i].node[1] - 1)) {
				sum += d[i].distance;
				unionParent(set, d[i].node[0] - 1, d[i].node[1] - 1);
			}
		}
		cout.precision(3);
		cout << sum << endl;
	}

	readFile.close();

	return 0;
}

/* whether nodes x and y have the same parent or not ==> !!!Check Cycled!!! */
bool sameParent(int parent[], int a, int b)    // 
{
	a = getParent(parent, a); // get a's parent
	b = getParent(parent, b); // get b's parent
	if (a == b) return true; // if same parent, return true
	else return false;
}

/* Get parent node  */
int getParent(int set[], int x)
{
	if (set[x] == x) return x;
	return set[x] = getParent(set, set[x]);
}

/* Union two Node...*/
void unionParent(int parent[], int a, int b)
{
	a = getParent(parent, a);
	b = getParent(parent, b);

	// Connect to the parent of either node ==> Be the same parent
	if (a != b) parent[b] = a;
}