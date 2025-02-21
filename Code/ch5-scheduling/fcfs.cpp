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

// Function to implement FCFS Scheduling
void fcfsScheduling(vector<Process> &processes) {
    int n = processes.size();
    int currentTime = 0;

    // Sorting processes based on Arrival Time (FCFS)
    sort(processes.begin(), processes.end(), [](Process a, Process b) {
        return a.arrival < b.arrival;
    });

    // Compute Completion Time, Turnaround Time, and Waiting Time
    for (int i = 0; i < n; i++) {
        if (currentTime < processes[i].arrival) {
            currentTime = processes[i].arrival; // Idle CPU until process arrives
        }
        processes[i].completion = currentTime + processes[i].burst;
        processes[i].turnaround = processes[i].completion - processes[i].arrival;
        processes[i].waiting = processes[i].turnaround - processes[i].burst;
        currentTime = processes[i].completion;
    }

    // Displaying Results
    cout << "\nFCFS Scheduling Results:\n";
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
        {1, 0, 5},  // Process ID 1, Arrival Time 0, Burst Time 5
        {2, 1, 3},  // Process ID 2, Arrival Time 1, Burst Time 3
        {3, 2, 8},  // Process ID 3, Arrival Time 2, Burst Time 8
        {4, 3, 6},  // Process ID 4, Arrival Time 3, Burst Time 6
        {5, 4, 4}   // Process ID 5, Arrival Time 4, Burst Time 4
    };

    // Run FCFS scheduling
    fcfsScheduling(processes);

    return 0;
}
