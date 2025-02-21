#include <iostream>
#include <unistd.h>

using namespace std;

int main() {
    for (int i = 0; i < 3; i++) {
        pid_t pid = fork();
        if (pid == 0) {  // Child process
            cout << "Child " << getpid() << " running.\n";
            while (true) { // Infinite loop (CPU intensive)
                for (volatile int i = 0; i < 1000000; i++);  // Burn CPU
            }
        }
    }

    while (true) { sleep(10); } // Keep parent alive
}
