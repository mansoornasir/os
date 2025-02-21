#include <iostream>
#include <vector>
#include <thread>
#include <algorithm>
#include <chrono>

using namespace std;
using namespace chrono;

void mergeSort(vector<int>& arr, int left, int right) {
    if (left >= right) return;
    int mid = left + (right - left) / 2;

    thread t1, t2;

    if (right - left > 100000) { // Use threading only for large chunks
        t1 = thread(mergeSort, ref(arr), left, mid);
        t2 = thread(mergeSort, ref(arr), mid + 1, right);
        t1.join();
        t2.join();
    } else {
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
    }

    inplace_merge(arr.begin() + left, arr.begin() + mid + 1, arr.begin() + right + 1);
}

int main() {
    int N = 10'000'000;
    vector<int> arr(N);

    // Generate random numbers
    for (int& num : arr) num = rand() % 1000000;

    auto start = high_resolution_clock::now();
    mergeSort(arr, 0, N - 1);
    auto end = high_resolution_clock::now();

    cout << "Multithreaded merge sort time: " << duration_cast<milliseconds>(end - start).count() << " ms" << endl;

    return 0;
}
