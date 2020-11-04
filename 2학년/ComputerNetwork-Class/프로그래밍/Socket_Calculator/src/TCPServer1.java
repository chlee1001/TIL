import java.io.*;
import java.net.*;

public class TCPServer1 {
	public static void main(String argv[]) throws Exception {
		String clientSentence = null;
		int portNumber = 5001;
		int answer = 0;

		ServerSocket welcomeSocket = new ServerSocket(portNumber);
		System.out.println("Starting Java Socket Server");
		System.out.println("Listening at port " + portNumber + " ...");

		while (true) {
			Socket connectionSocket = welcomeSocket.accept();

			BufferedReader inFromClient = new BufferedReader(new InputStreamReader(connectionSocket.getInputStream()));
			DataOutputStream outToClient = new DataOutputStream(connectionSocket.getOutputStream());
			InetAddress clientHost = connectionSocket.getLocalAddress();
			int clientPort = connectionSocket.getPort();
			System.out.println("A client connected. host: " + clientHost + ", port: " + clientPort);

			clientSentence = inFromClient.readLine();

			String word[] = clientSentence.split(" ");

			if (word.length > 3) {
				System.out.println("Too many arguments");
				outToClient.writeBytes("Error message: too many arguments\n");
			} else {
				if (word[0].equalsIgnoreCase("ADD")) {
					answer = Integer.parseInt(word[1]) + Integer.parseInt(word[2]);
					System.out.printf(word[1] + " + " + word[2] + " = " + answer + "\n");
					outToClient.writeBytes("Answer: " + answer + '\n');
				} else if (word[0].equalsIgnoreCase("MINUS")) {
					answer = Integer.parseInt(word[1]) - Integer.parseInt(word[2]);
					System.out.printf(word[1] + " - " + word[2] + " = " + answer + "\n");
					outToClient.writeBytes("Answer: " + answer + '\n');
				} else if (word[0].equalsIgnoreCase("DIV")) {
					if (Integer.parseInt(word[2]) == 0) {
						System.out.println("Incorrect: divided by zero\n");
						outToClient.writeBytes("Error message: divided by zero\n");
					} else {
						answer = Integer.parseInt(word[1]) / Integer.parseInt(word[2]);
						System.out.printf(word[1] + " / " + word[2] + " = " + answer + "\n");
						outToClient.writeBytes("Answer: " + answer + '\n');
					}
				} else if (word[0].equalsIgnoreCase("MULTIPLE")) {
					answer = Integer.parseInt(word[1]) * Integer.parseInt(word[2]);
					System.out.printf(word[1] + " * " + word[2] + " = " + answer + "\n");
					outToClient.writeBytes("Answer: " + answer + '\n');
				}

				// outToClient.writeBytes("Answer: " + answer + '\n');
			}
		}
	}
}