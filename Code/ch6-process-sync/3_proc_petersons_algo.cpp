#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>

using namespace std;
using namespace std::chrono;

atomic<bool> flag[3] = {false, false, false};  // Flags for three processes
atomic<int> turn = 0;  // Turn variable

void peterson(int process_id) {
    int next1 = (process_id + 1) % 3;  // Next process in sequence
    int next2 = (process_id + 2) % 3;

    // Entry Section
    flag[process_id] = true;
    turn = process_id;
    while ((flag[next1] || flag[next2]) && turn == process_id) {
        this_thread::yield();
    }

    // Critical Section
    cout << "Process " << process_id << " in critical section.\n";
    this_thread::sleep_for(milliseconds(1000));

    // Exit Section
    flag[process_id] = false;
    cout << "Process " << process_id << " left critical section.\n";
}

int main() {
    thread t1(peterson, 0);
    thread t2(peterson, 1);
    thread t3(peterson, 2);

    t1.join();
    t2.join();
    t3.join();

    return 0;
}
