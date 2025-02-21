#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;

void create_process(int n) {
    for (int i = 0; i < n; i++) {
        pid_t pid = fork();

        if (pid == 0) {  // Child process
            cout << "Child Process PID: " << getpid() << " started.\n";
            while (true) {  // Infinite loop to keep the process alive
                usleep(100000);  // Simulate work (100ms sleep)
            }
        } else {
            cout << "Parent created child: " << pid << endl;
        }
    }
}

int main() {
    int num_processes = 3; // Number of child processes
    create_process(num_processes);

    // Parent process monitoring
    while (true) {
        sleep(5);
    }

    return 0;
}


// cat /proc/$(pgrep context_switch | head -n 1)/status | grep ctxt
// vmstat 1
// pidstat -w 1 -> per process cs

// cswch/s: Voluntary context switches per second
// nvcswch/s: Non-voluntary context switches per second

// increase load to see more context switches
// dd if=/dev/zero of=/dev/null &
// find / > /dev/null &
