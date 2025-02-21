#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

using namespace std;

int main() {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in address = {AF_INET, htons(8080), INADDR_ANY};

    bind(server_fd, (struct sockaddr*)&address, sizeof(address));
    listen(server_fd, 3);

    int client_fd = accept(server_fd, NULL, NULL);
    char buffer[100] = {0};
    read(client_fd, buffer, 100);
    cout << "Server received: " << buffer << endl;

    close(client_fd);
    close(server_fd);
    return 0;
}
