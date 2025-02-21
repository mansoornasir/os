#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

// Structure to hold process information
struct Process {
    int id;         // Process ID
    int arrival;    // Arrival Time
    int burst;      // Burst Time
    int remaining;  // Remaining Time (for SRTF)
    int completion; // Completion Time
    int turnaround; // Turnaround Time
    int waiting;    // Waiting Time
};

// Function to implement SRTF Scheduling
void srtfScheduling(vector<Process>& processes) {
    int n = processes.size();
    int completed = 0, currentTime = 0, prevProcess = -1;
    vector<int> ganttChart;
    
    // Initialize remaining burst times
    for (auto &p : processes) {
        p.remaining = p.burst;
    }

    while (completed < n) {
        int shortest = -1;
        int minRemaining = INT_MAX;

        // Find the process with the shortest remaining time
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival <= currentTime && processes[i].remaining > 0) {
                if (processes[i].remaining < minRemaining) {
                    minRemaining = processes[i].remaining;
                    shortest = i;
                }
            }
        }

        if (shortest == -1) {
            currentTime++;
            continue;
        }

        // If a new process is selected, store it in the Gantt Chart
        if (prevProcess != processes[shortest].id) {
            ganttChart.push_back(processes[shortest].id);
        }

        // Process the shortest remaining job for 1 unit of time
        processes[shortest].remaining--;
        currentTime++;
        prevProcess = processes[shortest].id;

        // If process is completed
        if (processes[shortest].remaining == 0) {
            completed++;
            processes[shortest].completion = currentTime;
            processes[shortest].turnaround = processes[shortest].completion - processes[shortest].arrival;
            processes[shortest].waiting = processes[shortest].turnaround - processes[shortest].burst;
        }
    }

    // Display Results
    cout << "\nSRTF Scheduling Results:\n";
    cout << "-----------------------------------------------------\n";
    cout << "PID  Arrival  Burst  Completion  Turnaround  Waiting\n";
    cout << "-----------------------------------------------------\n";
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
        {2, 2, 8},  // Process ID 2, Arrival Time 2, Burst Time 8
        {3, 4, 7},  // Process ID 3, Arrival Time 4, Burst Time 7
        {4, 6, 3},  // Process ID 4, Arrival Time 6, Burst Time 3
        {5, 8, 4}   // Process ID 5, Arrival Time 8, Burst Time 4
    };

    // Run SRTF scheduling
    srtfScheduling(processes);

    return 0;
}
