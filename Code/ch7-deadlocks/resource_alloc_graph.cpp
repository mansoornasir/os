#include <iostream>
#include <vector>

using namespace std;

class RAG {
private:
    int numProcesses, numResources;
    vector<vector<int>> adjMatrix; // Adjacency matrix for RAG

public:
    RAG(int p, int r) : numProcesses(p), numResources(r) {
        adjMatrix.resize(p + r, vector<int>(p + r, 0)); // Graph matrix
    }

    // Add an edge (Process requesting Resource)
    void addRequestEdge(int process, int resource) {
        adjMatrix[process][numProcesses + resource] = 1;
    }

    // Add an edge (Resource allocated to Process)
    void addAssignmentEdge(int resource, int process) {
        adjMatrix[numProcesses + resource][process] = 1;
    }

    // Detect cycle using DFS (to find deadlock)
    bool detectCycleUtil(int node, vector<bool> &visited, vector<bool> &stack) {
        if (!visited[node]) {
            visited[node] = true;
            stack[node] = true;

            for (int i = 0; i < numProcesses + numResources; i++) {
                if (adjMatrix[node][i]) {
                    if (!visited[i] && detectCycleUtil(i, visited, stack))
                        return true;
                    else if (stack[i])
                        return true;
                }
            }
        }
        stack[node] = false;
        return false;
    }

    // Check for deadlock
    bool isDeadlock() {
        vector<bool> visited(numProcesses + numResources, false);
        vector<bool> stack(numProcesses + numResources, false);

        for (int i = 0; i < numProcesses + numResources; i++) {
            if (!visited[i] && detectCycleUtil(i, visited, stack)) {
                return true; // Cycle detected → Deadlock exists
            }
        }
        return false;
    }
};

int main() {
    int numProcesses = 3;
    int numResources = 3;
    
    RAG graph(numProcesses, numResources);

    // Example 1: Deadlock scenario
    graph.addRequestEdge(0, 1);  // P0 → R1
    graph.addAssignmentEdge(1, 0); // R1 → P0
    graph.addRequestEdge(1, 2);  // P1 → R2
    graph.addAssignmentEdge(2, 1); // R2 → P1
    graph.addRequestEdge(2, 0);  // P2 → R0
    graph.addAssignmentEdge(0, 2); // R0 → P2

    cout << "Checking for deadlock...\n";
    if (graph.isDeadlock()) {
        cout << "🔴 Deadlock detected!\n";
    } else {
        cout << "✅ No deadlock in the system.\n";
    }

    return 0;
}
