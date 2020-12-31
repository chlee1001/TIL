#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

void solution(int wayCnt, int detailCnt, string startTime, string startPoint, string endPoint, int visit);

struct description {
	string time;
	string locale;
}Descript[100][100];


int main()
{

	ifstream readFile;
	readFile.open("contestTrip.txt");    // Open File
	if (readFile.fail()) {
		cout << "Failed to open file." << endl;
		return 1;
	}

	int scenario = 0;
	int cityCnt = 0;
	string city[100];

	int wayCnt = 0;
	int detailCnt = 0;

	string startTime;
	string startPoint;
	string endPoint;
	int visit = 0;

	if (readFile.is_open()) {
		readFile >> scenario;

		for (int i = 0; i < scenario; i++) {
			readFile >> cityCnt;
			for (int j = 0; j < cityCnt; j++) {
				readFile >> city[j];
			}
			readFile >> wayCnt;
			for (int k = 0; k < wayCnt; k++) {
				readFile >> detailCnt;
				for (int l = 0; l < detailCnt; l++) {
					readFile >> Descript[k][l].time;
					readFile >> Descript[k][l].locale;
				}
			}

			readFile >> startTime;
			readFile >> startPoint;
			readFile >> endPoint;

			solution(wayCnt, detailCnt, startTime, startPoint, endPoint, ++visit);
		}
	}
	readFile.close();
}

void solution(int wayCnt, int detailCnt, string startTime, string start, string destination, int visit)
{
	int timeLimit = 2359;
	int detail_endPoint = 0;
	int onetimeFlag = 0;
	int flag = -1;
	int printFlag = 0;
	description result[2];
	while (flag != 0) {
		for (int i = 0; i < wayCnt; i++) {
			for (int j = 0; j < detailCnt; j++) {
				if (Descript[i][j].locale == destination) {
					string check = Descript[i][j].time;
					if ((stoi(check) < timeLimit) && (stoi(check) >= stoi(startTime))) {
						timeLimit = stoi(check);
						detail_endPoint = i;
					}
				}
			}
		}
	

		string disconnectCheck = Descript[detail_endPoint][0].time;
		if ((Descript[detail_endPoint][0].locale == start) && (stoi(disconnectCheck) > stoi(startTime))) {
			if (onetimeFlag == 0) {
				cout << "Scenario " << visit << endl;
				cout << "Departure: " << Descript[detail_endPoint][0].time << " " << Descript[detail_endPoint][0].locale << endl;
				cout << "Arrival: " << Descript[detail_endPoint][1].time << " " << Descript[detail_endPoint][1].locale << endl;
				printFlag = 1;
				flag = 0;
			}
			else {
				cout << "Scenario " << visit << endl;
				cout << "Departure: " << Descript[detail_endPoint][0].time << " " << Descript[detail_endPoint][0].locale << endl;
				cout << "Arrival: " << result[1].time << " " << result[1].locale << endl;
				printFlag = 1;
				flag = 0;
			}
		}
		else {
			result[1] = Descript[detail_endPoint][1];
			string check = Descript[detail_endPoint][0].locale;
			onetimeFlag = 1;
			destination = check;
		}
	}
	if (printFlag == 0) {
		cout << "Scenario " << visit << endl;
		cout << "No Connection" << endl;
	}
}