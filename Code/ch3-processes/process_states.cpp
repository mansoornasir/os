#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

using namespace std;

int main() {
    pid_t pid = fork();

    if (pid == 0) {
        // Child Process (Sleeping)
        cout << "Child: Sleeping for 10 seconds (Interruptible Sleep)\n";
        sleep(10);  
        cout << "Child: Exiting now.\n";
    } else {
        // Parent Process
        cout << "Parent: Child PID = " << pid << "\n";
        sleep(2);  // Let the child sleep
        
        cout << "Parent: Checking states using 'ps'.\n";
        system(("ps -o pid,stat,cmd -p " + to_string(pid)).c_str());

        cout << "Parent: Sending SIGSTOP (T - Stopped)\n";
        kill(pid, SIGSTOP);
        system(("ps -o pid,stat,cmd -p " + to_string(pid)).c_str());

        cout << "Parent: Sending SIGCONT (Resuming)\n";
        kill(pid, SIGCONT);
        system(("ps -o pid,stat,cmd -p " + to_string(pid)).c_str());

        sleep(12); // Let child exit, become zombie

        cout << "Parent: Checking zombie state (Z)\n";
        system(("ps -o pid,stat,cmd -p " + to_string(pid)).c_str());

        cout << "Parent: Calling wait() to clean zombie.\n";
        wait(NULL);
        system(("ps -o pid,stat,cmd -p " + to_string(pid)).c_str());

        cout << "Parent: Exiting now.\n";
    }

    return 0;
}


// cat /proc/12345/status
// ls -l /proc/12345/fd
// cat /proc/12345/sched
