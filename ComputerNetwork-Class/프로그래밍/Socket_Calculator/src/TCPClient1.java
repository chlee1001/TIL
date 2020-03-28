import java.io.*;
import java.net.*;

public class TCPClient1 {
	public static void main(String argv[]) throws Exception {
		int portNumber = 0;
		String ipAddress = "";
		String sentence = "";
		String result;

		try {
			FileInputStream serverinfo = new FileInputStream("serverinfo.dat");
			int temp_c;
			String temp_s = "";
			while ((temp_c = serverinfo.read()) != -1) {
				temp_s = temp_s + (char) temp_c;
			}
			serverinfo.close();

			String info[] = temp_s.split(" ");
			ipAddress = info[0];
			portNumber = Integer.parseInt(info[1]);
			System.out.println("IP Address: " + ipAddress + " portNumber: " + portNumber);

		} catch (FileNotFoundException e) {
			System.out.println(e.getMessage());
		} catch (Exception e) {
			System.out.println("오류가 발생하였습니다.");
		}

		while (true) {
			System.out.printf("Input:");
			BufferedReader inFromUser = new BufferedReader(new InputStreamReader(System.in));

			Socket clientSocket = new Socket(ipAddress, portNumber);

			DataOutputStream outToServer = new DataOutputStream(clientSocket.getOutputStream());

			BufferedReader inFromServer = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));

			sentence = inFromUser.readLine();

			outToServer.writeBytes(sentence + '\n');

			result = inFromServer.readLine();

			System.out.println(result);

			clientSocket.close();

		}

	}
}
