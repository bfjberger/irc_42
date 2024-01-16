/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvong <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 13:49:00 by pvong             #+#    #+#             */
/*   Updated: 2024/01/16 12:17:36 by pvong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server() {
    _serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (_serverSocket < 0) {
        std::cerr << "Error: socket creation failed." << std::endl;
        exit(EXIT_FAILURE);
    }

    _serverAddress.sin_family = AF_INET;
    _serverAddress.sin_addr.s_addr = INADDR_ANY;
    _serverAddress.sin_port = htons(8080);

    int bindResult = bind(_serverSocket, (struct sockaddr *)&_serverAddress, sizeof(_serverAddress));
    if (bindResult < 0) {
        std::cerr << "Error: socket binding failed: " << strerror(errno) << std::endl;
        close(_serverSocket);
        return ;
    }
    
    if (listen(_serverSocket, MAX_SOCKETS) < 0) {
        std::cerr << "Error: socket listening failed: " << strerror(errno) << std::endl;
        close(_serverSocket);
        return ;
    }

    std::cout << "Listening for connections on port " << PORT << "..." << std::endl;
}

Server::~Server() {
    close(_serverSocket);
}

void Server::run() {
    while (true) {
        struct sockaddr_in clientAddress; // clientAddress is the address of the client that is connecting to the server
        socklen_t clientAddressSize = sizeof(clientAddress); // clientAddressSize is the size of the clientAddress struct

        int clientSocket = accept(_serverSocket, (struct sockaddr *)&clientAddress, &clientAddressSize); // accept() returns a new socket file descriptor for the accepted connection
        if (clientSocket < 0) {
            std::cerr << "Error: socket accepting failed: " << strerror(errno) << std::endl;
            continue;
        }

        std::cout << "Connection accepted from client " << clientSocket << std::endl;
        
        // Create a thread to handle the connection
        pthread_t client_handler_thread;
        if (pthread_create(&client_handler_thread, NULL, handle_client, (void *)&clientSocket) < 0) {
            std::cerr << "Error: thread creation failed: " << strerror(errno) << std::endl;
            close(clientSocket);
            continue;
        }

        // Detach the thread to allow it to run independently
        pthread_detach(client_handler_thread);
    }
    close(_serverSocket);
}

// parse the client message
Message Server::parse_message(std::string message) {
    Message parsedMessage;
    
    // prefix
    std::cout << "Message: " << message << std::endl;
    if (message[0] == ':') {
        parsedMessage.prefix = message.substr(1, message.find(' ') - 1);
        std::cout << "Prefix: " << parsedMessage.prefix << std::endl;
        message = message.substr(message.find(' ') + 1);
    }

    // command
    parsedMessage.command = message.substr(0, message.find(' '));
    message = message.substr(message.find(' ') + 1);
    std::cout << "Command: " << parsedMessage.command << std::endl;

    // params
    while (message.find(' ') != std::string::npos) {
        parsedMessage.params.push_back(message.substr(0, message.find(' ')));
        message = message.substr(message.find(' ') + 1);
    }
    // show params
    std::cout << "Params: ";
    for (std::vector<std::string>::iterator it = parsedMessage.params.begin(); it != parsedMessage.params.end(); it++) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // body
    parsedMessage.body = message;

    return (parsedMessage);
}

// handle the client connection
void *Server::handle_client(void *clientSocket) {
    int clientSocketFd = *(int *)clientSocket;
    char buffer[1024] = {0};
    int readResult;

    while ((readResult = read(clientSocketFd, buffer, 1024)) > 0) {
        std::cout << "=====================" << std::endl;
        std::cout << "Received message from client " << clientSocketFd << ": " << buffer << std::endl;
        std::cout << "=====================" << std::endl;
        // send a confirmation message to the client
        std::string confirmation = "Message received\n";
        send(clientSocketFd, confirmation.c_str(), confirmation.length(), 0);
    }
    close(clientSocketFd);

    pthread_exit(NULL);
    return (NULL);
}
            
