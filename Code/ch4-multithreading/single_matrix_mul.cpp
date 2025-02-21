#include <iostream>
#include <vector>
#include <chrono>

using namespace std;
using namespace chrono;

const int N = 1000;
vector<vector<int>> A(N, vector<int>(N, 1));
vector<vector<int>> B(N, vector<int>(N, 1));
vector<vector<int>> C(N, vector<int>(N, 0));

void multiplyMatrix() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

int main() {
    auto start = high_resolution_clock::now();
    multiplyMatrix();
    auto end = high_resolution_clock::now();

    cout << "Single-threaded matrix multiplication time: " << duration_cast<milliseconds>(end - start).count() << " ms" << endl;

    return 0;
}

