#include <iostream>
#include <thread>
#include <vector>
#include <atomic>
#include <chrono>
#include <algorithm> // For max_element

using namespace std;
using namespace std::chrono;

const int N = 5;       // Number of processes
atomic<bool> flag[N];  // Process wants to enter
atomic<int> ticket[N]; // Ticket number for ordering

void bakery(int process_id)
{
    // Entry Section
    flag[process_id] = true;
    ticket[process_id] = 1 + *max_element(ticket, ticket + N); // Get max ticket and increment
    flag[process_id] = false;

    for (int i = 0; i < N; i++)
    {
        while (flag[i])
        {
        } // Wait for ticket assignment
        while (ticket[i] != 0 && (ticket[i] < ticket[process_id] ||
                                  (ticket[i] == ticket[process_id] && i < process_id)))
        {
            this_thread::yield();
        }
    }

    // Critical Section
    cout << "Process " << process_id << " in critical section.\n";
    this_thread::sleep_for(milliseconds(1000));

    // Exit Section
    ticket[process_id] = 0;
    cout << "Process " << process_id << " left critical section.\n";
}

int main()
{
    vector<thread> threads;
    for (int i = 0; i < N; i++)
    {
        threads.push_back(thread(bakery, i));
    }

    for (auto &t : threads)
    {
        t.join();
    }

    return 0;
}
