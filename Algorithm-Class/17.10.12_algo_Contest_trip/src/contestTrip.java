import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;
import java.math.*;

public class contestTrip {

	// private static double MAX = Math.pow(2, 1000);
	// static double[][] matrix;
	static int way;
	static int detailWay;

	static String temp = null;

	public static void main(String[] args) {
		String fileName = "Contest_trip.txt";
		Scanner inputStream = null;
		try {
			inputStream = new Scanner(new File(fileName));
		} catch (FileNotFoundException e) {
			System.out.println("Error opening the file " + fileName);
			System.exit(0);
		}

		int graphCnt = inputStream.nextInt();
		int visit = 0;
		for (int i = 0; i < graphCnt; i++) {

			int cityCnt = inputStream.nextInt();
			String[] city = new String[cityCnt];

			for (int j = 0; j < cityCnt; j++) {
				city[j] = inputStream.next();
			}

			way = inputStream.nextInt();
			detailWay = inputStream.nextInt();
			String[][] point = new String[way][detailWay];
			temp = inputStream.nextLine();

			for (int k = 0; k < way; k++) {
				for (int l = 0; l < detailWay; l++) {
					point[k][l] = inputStream.nextLine();
				}
				if (k != way - 1) {
					detailWay = inputStream.nextInt();
					temp = inputStream.nextLine();
				}
			}

			String startTime = inputStream.next();
			String startPoint = inputStream.next();
			String endPoint = inputStream.next();

			solve(point, startTime, startPoint, endPoint, ++visit);

		}

	}

	public static void solve(String[][] point, String startTime, String sP, String eP, int visit) {
		int time = 2359, endPoint = 0, flag = -1, printFlag = 0, onetimeFlag = 0;
		String[] result = new String[2];

		while (flag != 0) {
			for (int i = 0; i < way; i++) {
				for (int j = 0; j < detailWay; j++) {
					if (point[i][j].contains(eP)) {
						String[] check = point[i][j].split(" ");
						if ((Integer.parseInt(check[0])) < time
								&& (Integer.parseInt(check[0]) >= Integer.parseInt(startTime))) {
							time = Integer.parseInt(check[0]);
							endPoint = i;
						}
					}
				}
			}

			String disconChek[] = point[endPoint][0].split(" ");
			if (point[endPoint][0].contains(sP) && (Integer.parseInt(disconChek[0]) >= Integer.parseInt(startTime))) {
				if (onetimeFlag == 0) {
					System.out.println("Scenario " + visit);
					System.out.println("Departure: " + point[endPoint][0]);
					System.out.println("Arrival: " + point[endPoint][1]);
					printFlag = 1;
					flag = 0;
				} else {
					System.out.println("Scenario " + visit);
					System.out.println("Departure: " + point[endPoint][0]);
					System.out.println("Arrival: " + result[1]);
					printFlag = 1;
					flag=0;
				}
			} else {
				result[1] = point[endPoint][1];
				String[] check = point[endPoint][0].split(" ");
				onetimeFlag =1;
				eP = check[1];

			}
		}
		if (printFlag == 0) {
			System.out.println("Scenario " + visit);
			System.out.println("No Connection");
		}
	}

}
