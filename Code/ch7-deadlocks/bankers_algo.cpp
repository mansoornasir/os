#include <iostream>
#include <vector>

using namespace std;

// Number of processes and resources
const int P = 5; // Number of processes
const int R = 3; // Number of resources

// Function to check if the system is in a safe state
bool isSafe(vector<vector<int>> &allocation, vector<vector<int>> &need, vector<int> &available) {
    vector<bool> finished(P, false);
    vector<int> work = available;
    vector<int> safeSequence;

    int count = 0;
    while (count < P) {
        bool found = false;
        for (int i = 0; i < P; i++) {
            if (!finished[i]) {
                // Check if the process can get its needed resources
                bool canAllocate = true;
                for (int j = 0; j < R; j++) {
                    if (need[i][j] > work[j]) {
                        canAllocate = false;
                        break;
                    }
                }

                // If resources can be allocated, simulate allocation
                if (canAllocate) {
                    for (int j = 0; j < R; j++)
                        work[j] += allocation[i][j];

                    safeSequence.push_back(i);
                    finished[i] = true;
                    found = true;
                    count++;
                }
            }
        }

        // If no process could be allocated, system is in unsafe state
        if (!found) {
            cout << "System is in an **unsafe** state!\n";
            return false;
        }
    }

    // If we reached here, system is in a **safe** state
    cout << "System is in a **safe** state.\nSafe Sequence: ";
    for (int i : safeSequence)
        cout << "P" << i << " ";
    cout << endl;

    return true;
}

// Function to request resources
bool requestResources(int processID, vector<int> &request, vector<vector<int>> &allocation, vector<vector<int>> &need, vector<int> &available) {
    // Check if request is within the limits
    for (int j = 0; j < R; j++) {
        if (request[j] > need[processID][j]) {
            cout << "Error: Process P" << processID << " requested more than needed!\n";
            return false;
        }
        if (request[j] > available[j]) {
            cout << "Process P" << processID << " must wait, not enough resources available.\n";
            return false;
        }
    }

    // Temporarily allocate resources
    for (int j = 0; j < R; j++) {
        available[j] -= request[j];
        allocation[processID][j] += request[j];
        need[processID][j] -= request[j];
    }

    // Check if system remains in a safe state
    if (isSafe(allocation, need, available)) {
        cout << "Request granted for P" << processID << "\n";
        return true;
    } else {
        // Rollback allocation
        for (int j = 0; j < R; j++) {
            available[j] += request[j];
            allocation[processID][j] -= request[j];
            need[processID][j] += request[j];
        }
        cout << "Request denied for P" << processID << " to maintain a safe state.\n";
        return false;
    }
}

int main() {
    // Example resources
    vector<int> available = {3, 3, 2}; // Initially available resources

    // Maximum demand matrix
    vector<vector<int>> maxDemand = {
        {7, 5, 3},
        {3, 2, 2},
        {9, 0, 2},
        {2, 2, 2},
        {4, 3, 3}
    };

    // Allocation matrix (current resource allocation)
    vector<vector<int>> allocation = {
        {0, 1, 0},
        {2, 0, 0},
        {3, 0, 2},
        {2, 1, 1},
        {0, 0, 2}
    };

    // Calculate need matrix
    vector<vector<int>> need(P, vector<int>(R));
    for (int i = 0; i < P; i++)
        for (int j = 0; j < R; j++)
            need[i][j] = maxDemand[i][j] - allocation[i][j];

    // Check initial system safety
    isSafe(allocation, need, available);

    // Example resource request
    vector<int> request = {1, 0, 2}; // Process P1 requests (1,0,2)
    requestResources(1, request, allocation, need, available);

    return 0;
}
