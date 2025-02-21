#include <iostream>
#include <unistd.h>

using namespace std;

int main() {
    pid_t pid = getpid();  // Get Process ID
    cout << "Process ID: " << pid << endl;

    // Infinite loop to keep the process running
    while (true) {
        sleep(10);
    }

    return 0;
}
