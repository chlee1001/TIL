#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Time {
	int works;
	int start_hh, end_hh;
	int start_mm, end_mm;
	char temp;
}time[10][10];


int fileLoad()
{
	FILE* fp;
	char strTemp[255]; // Temporarily receives a single line of text.
	char* pStr; // Contains a split string.
	int days = 0; // how many datasets.... in text
	int i = 0, j = 0;

	fp = fopen("sweet_nap.txt", "r");
	if (fp == NULL) { // Check availiable file
		printf("Could not open sweet_nap.txt!\n");
		exit(1);
	}

	/* Load the text on file and Split the time to hh:mm */
	while (feof(fp) == 0) {
		fscanf(fp, "%d", &time[i][0].works);
		fscanf(fp, "%c", &time[i][0].temp);

		if (time[i][0].works == 0) { // if no works on the day.. then goto next day
			days++;

		}
		else {
			days++; // count day
			for (int j = 0; j < time[i][0].works; j++)
			{
				pStr = fgets(strTemp, sizeof(strTemp), fp);
				pStr = strtok(pStr, ":");
				time[i][j].start_hh = atoi(pStr);
				pStr = strtok(NULL, " ");
				time[i][j].start_mm = atoi(pStr);
				pStr = strtok(NULL, ":");
				time[i][j].end_hh = atoi(pStr);
				pStr = strtok(NULL, " ");
				time[i][j].end_mm = atoi(pStr);
			}
			i++;
		}
	}
	fclose(fp);
	return days;
}

int main()
{
	int days = fileLoad();

	int i = 0, j = 0;
	for (i = 0; i < days; i++) {
		int break_time = 0; // minute
		int last_break_time = 0;
		int start_nap_hh = 0, start_nap_mm = 0;


		for (j = 0; j < time[i][0].works - 1; j++) {
			break_time = 0;
			break_time += (time[i][j + 1].start_hh - time[i][j].end_hh) * 60; // add the hour's difference
			break_time += time[i][j + 1].start_mm - time[i][j].end_mm; // add the minute's difference
			if (last_break_time < break_time) {
				last_break_time = break_time;
				start_nap_hh = time[i][j].end_hh;
				start_nap_mm = time[i][j].end_mm;
			}
			break_time = last_break_time;
		}

		/* 18:00 - last ending time */
		last_break_time = 0;
		if ((time[i][j].end_hh < 18) && (time[i][j].end_mm < 60)) {
			last_break_time += (17 - time[i][j].end_hh) * 60;
			last_break_time += (60 - time[i][j].end_mm);
		}
		else if ((time[i][j].end_hh == 17) && (time[i][j].end_mm < 60)) {
			last_break_time += (60 - time[i][j].end_mm);
		}

		if (last_break_time > break_time) { // if  18:00 - last ending time > intermediate rest time
			break_time = last_break_time;
			start_nap_hh = time[i][j].end_hh;
			start_nap_mm = time[i][j].end_mm;
		}

		if (start_nap_mm != 0) {
			printf("Day #%d the longest nap starts at %d:%d and will last for %d hours and %d minutes.\n", i + 1, start_nap_hh, start_nap_mm, break_time / 60, break_time % 60);
		}
		else {
			printf("Day #%d the longest nap starts at %d:00 and will last for %d hours and %d minutes.\n", i + 1, start_nap_hh, break_time / 60, break_time % 60);
		}
	}
	return 0;
}