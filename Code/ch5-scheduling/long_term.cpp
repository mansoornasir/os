#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <vector>
#include <sys/wait.h>

using namespace std;

int main() {
    int num_processes = 20;
    vector<pid_t> pids;

    for (int i = 0; i < num_processes; i++) {
        pid_t pid = fork();

        if (pid == 0) {  // Child process
            cout << "Child " << getpid() << " created.\n";
            sleep(10);  // Simulate process execution
            return 0;
        } else {
            pids.push_back(pid);
        }
    }

    // Parent waits for all children
    for (pid_t pid : pids) {
        waitpid(pid, NULL, 0);
    }

    return 0;
}
