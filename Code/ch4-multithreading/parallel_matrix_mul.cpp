#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

using namespace std;
using namespace chrono;

const int N = 1000;
vector<vector<int>> A(N, vector<int>(N, 1));
vector<vector<int>> B(N, vector<int>(N, 1));
vector<vector<int>> C(N, vector<int>(N, 0));

void multiplyRow(int row) {
    for (int j = 0; j < N; j++) {
        for (int k = 0; k < N; k++) {
            C[row][j] += A[row][k] * B[k][j];
        }
    }
}

int main() {
    vector<thread> threads;

    auto start = high_resolution_clock::now();

    for (int i = 0; i < N; i++)
        threads.emplace_back(multiplyRow, i);

    for (auto& t : threads)
        t.join();

    auto end = high_resolution_clock::now();

    cout << "Multithreaded matrix multiplication time: " << duration_cast<milliseconds>(end - start).count() << " ms" << endl;

    return 0;
}

