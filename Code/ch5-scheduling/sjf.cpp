#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm> // Required for sorting

using namespace std;

// Structure to hold process information
struct Process {
    int id;         // Process ID
    int arrival;    // Arrival Time
    int burst;      // Burst Time
    int completion; // Completion Time
    int turnaround; // Turnaround Time
    int waiting;    // Waiting Time
};

// Function to implement SJF Scheduling (Non-Preemptive)
void sjfScheduling(vector<Process> &processes) {
    int n = processes.size();
    int currentTime = 0;
    vector<bool> isCompleted(n, false);
    int completed = 0;

    // Sorting based on Arrival Time
    sort(processes.begin(), processes.end(), [](Process a, Process b) {
        return a.arrival < b.arrival;
    });

    // Scheduling Processes
    while (completed < n) {
        int shortest = -1;
        int minBurst = 1e9; // Set to a large value initially

        // Find the process with the shortest burst time that has arrived
        for (int i = 0; i < n; i++) {
            if (!isCompleted[i] && processes[i].arrival <= currentTime) {
                if (processes[i].burst < minBurst) {
                    minBurst = processes[i].burst;
                    shortest = i;
                }
            }
        }

        // If no process is found, move to the next available process
        if (shortest == -1) {
            currentTime++;
        } else {
            processes[shortest].completion = currentTime + processes[shortest].burst;
            processes[shortest].turnaround = processes[shortest].completion - processes[shortest].arrival;
            processes[shortest].waiting = processes[shortest].turnaround - processes[shortest].burst;
            currentTime = processes[shortest].completion;
            isCompleted[shortest] = true;
            completed++;
        }
    }

    // Displaying Results
    cout << "\nSJF Scheduling Results:\n";
    cout << "-----------------------------------------------------\n";
    cout << "PID  Arrival  Burst  Completion  Turnaround  Waiting\n";
    cout << "-----------------------------------------------------\n";
    for (const auto &p : processes) {
        cout << setw(3) << p.id << "   " << setw(6) << p.arrival << "   "
             << setw(5) << p.burst << "   " << setw(10) << p.completion << "   "
             << setw(10) << p.turnaround << "   " << setw(7) << p.waiting << "\n";
    }

    // Gantt Chart Visualization
    cout << "\nGantt Chart:\n";
    cout << " ";
    for (const auto &p : processes) {
        for (int i = 0; i < p.burst; i++) cout << "--";
        cout << " ";
    }
    cout << "\n|";

    for (const auto &p : processes) {
        for (int i = 0; i < p.burst - 1; i++) cout << " ";
        cout << "P" << p.id;
        for (int i = 0; i < p.burst - 1; i++) cout << " ";
        cout << "|";
    }
    cout << "\n ";

    for (const auto &p : processes) {
        for (int i = 0; i < p.burst; i++) cout << "--";
        cout << " ";
    }

    cout << "\n0";
    for (const auto &p : processes) {
        for (int i = 0; i < p.burst; i++) cout << "  ";
        cout << p.completion;
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

    // Run SJF scheduling
    sjfScheduling(processes);

    return 0;
}
