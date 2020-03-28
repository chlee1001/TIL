import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;
import java.math.*;

public class savingInk {

	private static double MAX = Math.pow(2, 1000);
	static double[][] matrix;
	static double[] distance;

	public static void main(String[] args) {
		String fileName = "Saving_ink.txt";
		Scanner inputStream = null;
		try {
			inputStream = new Scanner(new File(fileName));
		} catch (FileNotFoundException e) {
			System.out.println("Error opening the file " + fileName);
			System.exit(0);
		}

		int vertex = inputStream.nextInt();

		double[] xPtr = new double[vertex];
		double[] yPtr = new double[vertex];
		matrix = new double[vertex][vertex];
		distance = new double[vertex];

		for (int i = 0; i < vertex; i++) {
			xPtr[i] = inputStream.nextDouble();
			yPtr[i] = inputStream.nextDouble();
		}

		for (int i = 0; i < vertex; i++) {
			for (int j = i; j < vertex; j++) {
				matrix[i][j] = Math.sqrt((Math.pow((xPtr[i] - xPtr[j]), 2)) + (Math.pow((yPtr[i] - yPtr[j]), 2)));
				matrix[j][i] = matrix[i][j];
			}
		}

		double ans = prim(vertex);

		System.out.printf("%.2f\n",ans);
	}

	private static double prim(int n) {
		double result = 0.0;
		int current = 0;
		int next = -1;
		double min = 0;

		for (int i = 0; i < n; i++) {
			distance[i] = MAX;
		}

		for (int i = 1; i < n; i++) {
			distance[current] = -1;
			min = MAX;
			for (int j = 0; j < n; j++) {
				if (current != j && distance[j] > 0) {
					if (distance[j] > matrix[current][j]) {
						distance[j] = matrix[current][j];
					}

					if (distance[j] < min) {
						min = distance[j];
						next = j;
					}
				}
			}
			result += min;
			current = next;
		}

		return result;
	}

}
