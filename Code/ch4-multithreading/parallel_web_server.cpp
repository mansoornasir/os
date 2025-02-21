#include <iostream>
#include <thread>
#include <vector>
#include <arpa/inet.h>
#include <unistd.h>

using namespace std;

void handleClient(int clientSocket) {
    char buffer[1024] = {0};
    read(clientSocket, buffer, 1024);
    cout << "Client: " << buffer << endl;
    send(clientSocket, "Hello from server", 17, 0);
    close(clientSocket);
}

int main() {
    int serverSocket, newSocket;
    struct sockaddr_in serverAddr;
    socklen_t addrSize = sizeof(serverAddr);

    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    listen(serverSocket, 5);
    
    vector<thread> threads;

    while ((newSocket = accept(serverSocket, (struct sockaddr*)&serverAddr, &addrSize))) {
        threads.emplace_back(handleClient, newSocket);
    }

    for (auto& t : threads)
        t.join();

    close(serverSocket);
    return 0;
}

