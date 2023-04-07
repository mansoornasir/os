import java.net.*;
import java.io.*;

public class Server
{
	public static void main(String[] args) throws IOException {
		Socket client = null;
		PrintWriter pout = null;
		ServerSocket sock = null;

		try {
			sock = new ServerSocket(5155);

			// now listen for connections
			while (true) {
				client = sock.accept();

				// we have a connection
				pout = new PrintWriter(client.getOutputStream(), true);
				// write the Date to the socket
				pout.println(new java.util.Date().toString());

				pout.close();
				client.close();
			}
		}
		catch (IOException ioe) {
				System.err.println(ioe);
		}
		finally {
			if (sock != null)
				sock.close();
			if (client != null)
				client.close();
		}
	}
}
