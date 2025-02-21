#include <iostream>
#include <unistd.h>
#include <cstring>

using namespace std;

int main() {
    int fd[2];  // File descriptors: fd[0] = read, fd[1] = write
    pipe(fd);

    pid_t pid = fork();

    if (pid == 0) {  // Child Process
        close(fd[1]);  // Close write end
        char buffer[100];
        read(fd[0], buffer, sizeof(buffer));
        cout << "Child received: " << buffer << endl;
        close(fd[0]);
    } else {  // Parent Process
        close(fd[0]);  // Close read end
        const char* msg = "Hello from Parent!";
        write(fd[1], msg, strlen(msg) + 1);
        close(fd[1]);
    }

    return 0;
}
