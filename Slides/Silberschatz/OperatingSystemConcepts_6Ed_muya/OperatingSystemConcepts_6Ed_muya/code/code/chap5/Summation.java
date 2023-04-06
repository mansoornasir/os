public class Summation extends Thread
{
        public Summation(int n) {
                upper = n;
        }

        public void run() {
                int sum = 0;

                if (upper > 0) {
                        for (int i = 1; i <= upper; i++)
                                sum += i;
                }

                System.out.println("The summation of " + upper + " is " + sum);
        }

        private int upper;
}

