#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

const char* SERVER_IP = "127.0.0.1";
const int SERVER_PORT = 8080;

int main() {
    // Create socket
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        std::cerr << "Error creating socket" << std::endl;
        return -1;
    }

    // Set up server information
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(SERVER_PORT);
    if (inet_pton(AF_INET, SERVER_IP, &serverAddr.sin_addr) <= 0) {
        std::cerr << "Invalid address or address not supported" << std::endl;
        return -1;
    }

    // Connect to the server
    if (connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
        std::cerr << "Error connecting to server" << std::endl;
        return -1;
    }

    // Send a user and nickname message
    const char* nickname = "YourNickname";
    const char* username = "YourUsername";
    std::string userMessage = "USER " + std::string(username) + " 0 * :YourRealName\r\n";
    std::string nickMessage = "NICK " + std::string(nickname) + "\r\n";

    send(clientSocket, userMessage.c_str(), userMessage.size(), 0);
    send(clientSocket, nickMessage.c_str(), nickMessage.size(), 0);

    // Join a channel
    const char* channel = "#YourChannel";
    std::string joinMessage = "JOIN " + std::string(channel) + "\r\n";
    send(clientSocket, joinMessage.c_str(), joinMessage.size(), 0);

    // Main loop to receive and display messages
    char buffer[4096];
    while (true) {
        memset(buffer, 0, sizeof(buffer));
        ssize_t bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesRead <= 0) {
            std::cerr << "Connection closed by the server" << std::endl;
            break;
        }

        std::cout << buffer;
    }

    // Close the socket
    close(clientSocket);

    return 0;
}
