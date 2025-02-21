// τ(n+1)=α⋅t(n)+(1−α)⋅τ(n)

#include <iostream>
#include <vector>

using namespace std;

// Function to predict the next CPU burst time using the formula
double predictBurstTime(double prevTau, double actualBurst, double alpha) {
    return alpha * actualBurst + (1 - alpha) * prevTau;
}

int main() {
    double alpha = 0.5;  // Smoothing factor (adjust as needed)
    double tau0 = 5.0;   // Initial guess for burst time (τ(0))
    
    vector<double> actualBursts = {6, 4, 7, 5, 3,3,2,54,6,4,2,3,3,5,6,34,3}; // Given burst times
    vector<double> predictedBursts;

    double currentTau = tau0;
    
    cout << "Initial Predicted Burst Time: " << tau0 << endl;

    for (size_t i = 0; i < actualBursts.size(); i++) {
        double newTau = predictBurstTime(currentTau, actualBursts[i], alpha);
        predictedBursts.push_back(newTau);
        
        cout << "CPU Burst " << i + 1 << " | Actual: " << actualBursts[i]
             << " | Predicted: " << newTau << endl;
        
        currentTau = newTau;  // Update prediction for the next burst
    }

    return 0;
}
