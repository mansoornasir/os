#include <iostream>
#include <iomanip>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

// Structure to store process details
struct Process {
    int id;         // Process ID
    int arrival;    // Arrival Time
    int burst;      // Burst Time
    int completion;// Completion Time
    int turnaround;// Turnaround Time
    int waiting;   // Waiting Time
};

// Function to perform Non-Preemptive Round Robin Scheduling
void nonPreemptiveRoundRobin(vector<Process>& processes) {
    int n = processes.size();
    queue<int> readyQueue;
    vector<int> ganttChart;
    int currentTime = 0, completed = 0;

    // Sort processes based on arrival time
    sort(processes.begin(), processes.end(), [](Process a, Process b) {
        return a.arrival < b.arrival;
    });

    int index = 0;

    // Add processes arriving at time 0
    while (index < n && processes[index].arrival <= currentTime) {
        readyQueue.push(index);
        index++;
    }

    while (completed < n) {
        if (readyQueue.empty()) {
            currentTime++; // Move time forward if no process is in the queue
            while (index < n && processes[index].arrival <= currentTime) {
                readyQueue.push(index);
                index++;
            }
            continue;
        }

        int i = readyQueue.front();
        readyQueue.pop();

        // Process runs to completion
        currentTime = max(currentTime, processes[i].arrival) + processes[i].burst;
        processes[i].completion = currentTime;
        processes[i].turnaround = processes[i].completion - processes[i].arrival;
        processes[i].waiting = processes[i].turnaround - processes[i].burst;
        ganttChart.push_back(processes[i].id);
        completed++;

        // Add new processes that have arrived
        while (index < n && processes[index].arrival <= currentTime) {
            readyQueue.push(index);
            index++;
        }
    }

    // Display Process Table
    cout << "\nNon-Preemptive Round Robin Scheduling Results:\n";
    cout << "------------------------------------------------------\n";
    cout << "PID  Arrival  Burst  Completion  Turnaround  Waiting\n";
    cout << "------------------------------------------------------\n";
    for (const auto &p : processes) {
        cout << setw(3) << p.id << "   " << setw(6) << p.arrival << "   "
             << setw(5) << p.burst << "   " << setw(10) << p.completion << "   "
             << setw(10) << p.turnaround << "   " << setw(7) << p.waiting << "\n";
    }

    // Gantt Chart Visualization
    cout << "\nGantt Chart:\n ";
    for (size_t i = 0; i < ganttChart.size(); i++) {
        cout << "--";
    }
    cout << "\n|";

    for (size_t i = 0; i < ganttChart.size(); i++) {
        cout << "P" << ganttChart[i] << "|";
    }

    cout << "\n ";
    for (size_t i = 0; i < ganttChart.size(); i++) {
        cout << "--";
    }
    cout << "\n";
}

int main() {
    // Example with 5 processes
    vector<Process> processes = {
        {1, 0, 6},  // Process ID 1, Arrival Time 0, Burst Time 6
        {2, 1, 8},  // Process ID 2, Arrival Time 1, Burst Time 8
        {3, 2, 7},  // Process ID 3, Arrival Time 2, Burst Time 7
        {4, 3, 3},  // Process ID 4, Arrival Time 3, Burst Time 3
        {5, 4, 4}   // Process ID 5, Arrival Time 4, Burst Time 4
    };

    // Run Non-Preemptive Round Robin scheduling
    nonPreemptiveRoundRobin(processes);

    return 0;
}
