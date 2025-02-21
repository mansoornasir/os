#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>

using namespace std;
using namespace std::chrono;

// Shared variables
atomic<bool> flag[2] = {false, false};  // Flags for process 0 and 1
atomic<int> turn = 0;  // Determines whose turn it is

// Peterson's solution function
void peterson(int process_id) {
    int other = 1 - process_id;  // The other process ID

    // Entry Section
    flag[process_id] = true;  // Indicate interest in critical section
    turn = other;  // Give turn to the other process
    while (flag[other] && turn == other) {
        this_thread::yield();  // Wait until the other process exits
    }

    // Critical Section
    cout << "Process " << process_id << " is in the critical section.\n";
    this_thread::sleep_for(milliseconds(1000));  // Simulate some work

    // Exit Section
    flag[process_id] = false;  // Process leaves critical section
    cout << "Process " << process_id << " is leaving the critical section.\n";
}

int main() {
    thread t1(peterson, 0);  // Process 0
    thread t2(peterson, 1);  // Process 1

    t1.join();
    t2.join();

    return 0;
}
