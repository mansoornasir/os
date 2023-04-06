class Sum1 {
    private long sum;

    public long getSum() {
        return this.sum;
    }

    public void setSum(long sum) {
        this.sum = sum;
    }
}

class Summation1 {
    private int upper;
    private Sum1 sumValue;

    public Summation1(int upper, Sum1 sumValue) {
        this.upper = upper;
        this.sumValue = sumValue;
        long sum = 0;
        for (int i = 0; i <= upper; i++) {
            sum = sum + i;
        }

        sumValue.setSum(sum);
    }
}

public class WithoutMT {
    public static void main(String[] args) {
        long sum = 0;
        if (args.length > 0) {
            if (Integer.parseInt(args[0]) < 0)
                System.err.println(args[0] + " must be >= 0.");
            else {
                Sum1 sumObject = new Sum1();
                int upper = Integer.parseInt(args[0]);
                Summation1 s = new Summation1(upper, sumObject);
                System.out.println("The sum of " + upper + " is " + sumObject.getSum());

            }
        }
    }
}