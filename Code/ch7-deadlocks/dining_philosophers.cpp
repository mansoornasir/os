#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <chrono>

using namespace std;
using namespace std::chrono;

const int N = 5;  // Number of philosophers

mutex forks[N];  // Mutex for each fork

void philosopher(int id) {
    int leftFork = id;
    int rightFork = (id + 1) % N;

    while (true) {
        // Thinking
        cout << "Philosopher " << id << " is thinking...\n";
        this_thread::sleep_for(milliseconds(1000));

        // Pick up forks (Avoiding Deadlock)
        if (id == N - 1) {  // Last philosopher picks up right fork first
            forks[rightFork].lock();
            cout << "Philosopher " << id << " picked up right fork.\n";
            forks[leftFork].lock();
        } else {
            forks[leftFork].lock();
            cout << "Philosopher " << id << " picked up left fork.\n";
            forks[rightFork].lock();
        }

        // Eating
        cout << "Philosopher " << id << " is eating...\n";
        this_thread::sleep_for(milliseconds(1500));

        // Put down forks
        forks[leftFork].unlock();
        forks[rightFork].unlock();
        cout << "Philosopher " << id << " put down forks and is thinking again.\n";
    }
}

int main() {
    vector<thread> philosophers;

    for (int i = 0; i < N; i++) {
        philosophers.push_back(thread(philosopher, i));
    }

    for (auto &t : philosophers) {
        t.join();
    }

    return 0;
}
