#include <iostream>
#include <iomanip>  // For formatting output

using namespace std;

// Function to calculate speedup using Amdahl's Law
double amdahlsLaw(double p, int s) {
    if (s <= 0) {
        cerr << "Number of processors must be greater than zero." << endl;
        return 0;
    }
    return 1.0 / ((1 - p) + (p / s));
}

int main() {
    // Example values
    double p = 0.8;   // 80% of the task can be parallelized
    int sValues[] = {1, 2, 4, 8, 16};  // Different numbers of processors

    cout << "Parallel Fraction (p): " << p << endl;
    cout << "Processors | Speedup (S)" << endl;
    cout << "-------------------------" << endl;

    for (int s : sValues) {
        double speedup = amdahlsLaw(p, s);
        cout << setw(9) << s << "   | " << fixed << setprecision(2) << speedup << endl;
    }

    return 0;
}
