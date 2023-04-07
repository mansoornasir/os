/**
 * time-of-day Client.
 *
 * @author Greg Gagne, Avi Silberschatz, Peter Galvin - June 2001.
 *
 * Usage:
 *	java Client [host name]
 */

import java.net.*;
import java.io.*;

public class Client
{
	public static void main(String[] args) throws IOException {
		String host;

		if (args.length == 0)
			host = "127.0.0.1";
		else
			host = args[0].trim();
			
		InputStream in = null;
		BufferedReader bin = null;
		Socket sock = null;

		try {
			sock = new Socket(host, 5155);
			in = sock.getInputStream();
			bin = new BufferedReader(new InputStreamReader(in));

			String line;
			while( (line = bin.readLine()) != null)
				System.out.println(line);
		}
		catch (IOException ioe) {
				System.err.println(ioe);
		}
		finally {
			if (in != null)
				in.close();
			if (bin != null)
				bin.close();
			if (sock != null)
				sock.close();
		}
	}
}



