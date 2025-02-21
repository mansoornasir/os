#include <iostream>
#include <fstream>

int main() {
    std::fstream file;
    file.open("test.txt", std::ios::out); // Open a file for writing
    if (file.is_open()) {
        file << "Hello, world!" << std::endl;
        file.close();
    } else {
        std::cerr << "Failed to open file!" << std::endl;
    }
    return 0;
}

// strace ./file_open 2>&1 | grep -E 'open|openat' 
// will output something like this
// openat(AT_FDCWD, "test.txt", O_WRONLY|O_CREAT|O_TRUNC, 0666) = 3
