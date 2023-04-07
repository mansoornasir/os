public class ThreadTester
{
	public static void main(String[] args) {
		if (args.length > 0) {
			if (Integer.parseInt(args[0]) < 0)
				throw new IllegalArgumentException(args[0] + " must be non-negative.");
			else {
				Summation summationThread = new Summation(Integer.parseInt(args[0]));
				summationThread.start();
			}
		}
		else 
			System.err.println("Usage: Summation <integer value>");
	}       
}

