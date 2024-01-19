/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvong <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 13:49:00 by pvong             #+#    #+#             */
/*   Updated: 2024/01/19 11:45:04 by pvong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

/* -------------------------------------------------------------------------- */
/*                                   SERVER                                   */
/* -------------------------------------------------------------------------- */

/**
 * @brief Constructs a Server object with the specified port and password.
 * 
 *  The Server object is created with the following steps:
 * 1. A socket is created with socket()
 * 2. The socket is bound to an IP address and port with bind()
 * 3. The socket is set to listen for incoming connections with listen()
 *  
 * @param port The port number to listen for connections on.
 * @param password The password required for clients to connect to the server.
 */
Server::Server(const std::string port, const std::string password) : _port(port), _password(password) {
    _serverSocketFd = socket(AF_INET, SOCK_STREAM, 0);
    if (_serverSocketFd < 0) {
        std::cerr << COLOR("Error: socket creation failed.", RED) << std::endl;
        exit(EXIT_FAILURE);
    }

    _serverAddress.sin_family = AF_INET; // IPv4
    _serverAddress.sin_addr.s_addr = INADDR_ANY; // bind to all available interfaces
    _serverAddress.sin_port = htons(std::atoi(port.c_str())); // convert port to int and convert to network byte order

    int bindResult = bind(_serverSocketFd, (struct sockaddr *)&_serverAddress, sizeof(_serverAddress));
    if (bindResult < 0) {
        std::cerr << COLOR("Error: socket binding failed: ", RED) << strerror(errno) << std::endl;
        close(_serverSocketFd);
        return ;
    }
    
    if (listen(_serverSocketFd, MAX_SOCKETS) < 0) {
        std::cerr << COLOR("Error: socket listening failed: ", RED) << strerror(errno) << std::endl;
        close(_serverSocketFd);
        return ;
    }

    std::cout << COLOR("Listening for connections on port ", CYAN) << port << COLOR(" with password: ", CYAN) << password << " ..." << std::endl;
}

Server::~Server() {
    std::cout << COLOR("Closing server socket...", CYAN) << std::endl;
    close(_serverSocketFd);
}

/* ---------------------------------- Poll ---------------------------------- */

// Pollfd is a struct with the following members:
// int fd;         // file descriptor
// short events;   // requested events
// short revents;  // returned events

// poll() is a function that waits for one of a set of file descriptors to become ready to perform I/O.
// poll() takes three arguments:
// 1. an array of pollfd structs
// 2. the number of elements in the array
// 3. a timeout in milliseconds (-1 means infinite timeout)

// poll() returns the number of elements in the array that have non-zero revents fields.
// If poll() returns 0, it means that the timeout expired and no file descriptors were ready.
// If poll() returns -1, it means that an error occurred.
// If poll() returns a positive number, it means that the file descriptor at that index in the array has data available to read.

// POLLIN: data can be read
// POLLOUT: data can be written
// POLLERR: an error occurred
// POLLHUP: the connection was closed
// POLLNVAL: the file descriptor is not open

/* -------------------------------------------------------------------------- */

/**
 * @brief Deletes a client from the list of connected clients.
 * 
 * This function removes the client with the specified socket file descriptor from the vector of pollfds.
 * It also closes the client socket and prints a message indicating that the client has been disconnected.
 * 
 * @param pollfds The vector of pollfds representing the connected clients.
 * @param clientSocketFd The socket file descriptor of the client to be deleted.
 */
void Server::deleteClient(std::vector<pollfd> &pollfds, int clientSocketFd) {
    std::vector<pollfd>::iterator it = pollfds.begin();
    while (it != pollfds.end()) {
        if (it->fd == clientSocketFd) {
            std::cout << COLOR("Client ", CYAN) << clientSocketFd << COLOR(" disconnected.", CYAN) << std::endl;
            close(it->fd);
            it = pollfds.erase(it);
            return ;
        }
        it++;
    }
}

/**
 * @brief Accepts a new client connection on the given listen socket.
 *      The client socket is added to the pollfds vector.
 * 
 * accept() is a function that accepts a connection on a socket.
 * accept() takes three arguments:
 * 1. the socket file descriptor on which to accept the connection
 * 2. a pointer to a sockaddr struct that will be filled with the client's address information
 * 3. a pointer to a socklen_t that will be filled with the size of the client's address information
 * 
 * accept() returns the file descriptor of the accepted client socket, or -1 if an error occurred.
 * 
 * @param listenSocket The listen socket on which to accept the connection.
 * @return The file descriptor of the accepted client socket, or -1 if an error occurred.
 */
static int acceptSocket(int listenSocket) {
    struct sockaddr_in clientAddress;
    socklen_t clientAddressSize = sizeof(clientAddress);
    int clientSocketFd = accept(listenSocket, (struct sockaddr *)&clientAddress, &clientAddressSize);
    if (clientSocketFd < 0) {
        std::cerr << COLOR("Error: socket accepting failed: ", RED) << strerror(errno) << std::endl;
        return (-1);
    }
    std::cout << COLOR("New connection from ", CYAN) << inet_ntoa(clientAddress.sin_addr) << COLOR(" on clientAddr port ", CYAN) << ntohs(clientAddress.sin_port) << std::endl;
    return (clientSocketFd);
}

void Server::addClient(int clientSocket, std::vector<pollfd> &pollfds) {
    pollfd clientPollfd;
    Client client(clientSocket);
    clientPollfd.fd = clientSocket;
    clientPollfd.events = POLLIN | POLLOUT; // data can be read and written
    pollfds.push_back(clientPollfd);
    _clients.insert(std::pair<int, Client>(clientSocket, client));
    std::cout << COLOR("Added client #", CYAN) << clientSocket << std::endl;    
}

void Server::handleMaxClient(int clientSocketFd) {
    std::cout << COLOR(ERR_MAX_CLIENTS, RED) << std::endl;
    send(clientSocketFd, ERR_MAX_CLIENTS, strlen(ERR_MAX_CLIENTS), 0);
    close(clientSocketFd);
}


// TODO: Working on the parsing to get the user info -> NICK, USER
static void splitMessage(std::vector<std::string> &cmds, std::string msg) {
    int pos = 0;
    std::string delimiter = "\n";
    std::string substr;

    while ((pos = msg.find(delimiter)) != static_cast<int>(std::string::npos)) {
        substr = msg.substr(0, pos);
        cmds.push_back(substr);
        msg.erase(0, pos + delimiter.length());
    }
}

// TODO: Working on it
std::string tmpFormatString(std::string msg) {
    if (msg.find(' ') != std::string::npos && msg.find(' ') == 0) {
        msg.erase(msg.find(' '), 1);
    }
    if  (msg.find('\r') != std::string::npos ) {
        msg.erase(msg.find('\r'), 1);
    }
    return msg;
}

// TODO: Working on it
void Server::fillUserInfo(std::map<const int, Client> &clients, int clientSocketFd, std::string msg) {
    // std::map<const int, Client>::iterator it = clients.find(clientSocketFd);
    (void) clients, (void) clientSocketFd;
    std::cout << "fillUserInfo msg: " << msg << std::endl;

    // TODO: CHECK FOR PASS
}

// TODO: Working on it
void Server::parseMessage(std::string message, int clientSocketFd) {
    std::vector<std::string> cmds;
    std::map<const int, Client>::iterator it = _clients.find(clientSocketFd);
    std::cout << "parseMessage msg: " << message << std::endl;
    splitMessage(cmds, message);

    for (size_t i = 0; i != cmds.size(); i++) {
        if (it->second.isLogged() == false) {
            fillUserInfo(_clients, clientSocketFd, cmds[i]);
            if (it->second.getNick() != "" && it->second.getUserName() != "") {
                it->second.setReceivedInfo(true);
            }
        }
    }
    it->second.printInfo();
}

/**
 * @brief Runs the server and handles incoming connections and data.
 * 
 * This function continuously polls for events on the server socket and client sockets.
 * It accepts new connections, reads data from existing connections, and handles errors and disconnections.
 * 
 * Steps:
 * 1. Create a vector of pollfds with the server socket
 * 2. Poll for events on the pollfds
 * 3. If the server socket has an event, accept the connection and add the client socket to the pollfds
 * 4. If a client socket has an event, read the data and parse it
 * 5. If an error occurs, delete the client from the pollfds
 * 6. If the client disconnects, delete the client from the pollfds
 * 7. If the poll() call returns -1, an error occurred
 * 8. If the poll() call returns 0, the timeout expired and no file descriptors were ready
 * 9. If the poll() call returns a positive number, the file descriptor at that index in the array has data available to read
 * 
 * TODO: 
 * The received data is to be parsed according to the IRC protocol, and appropriate responses are sent.
 * 
 * @note This function runs indefinitely until an error occurs or all clients disconnect.
 */
void Server::run() {
    std::vector<pollfd> pollfds;
    pollfd serverPollfd;
    serverPollfd.fd = _serverSocketFd;
    serverPollfd.events = POLLIN;
    pollfds.push_back(serverPollfd);

    while (true) {
        std::vector<pollfd> newPollfds;

        if (poll(&pollfds[0], pollfds.size(), -1) == -1) {
            std::cerr << COLOR("Error: poll failed: ", RED) << strerror(errno) << std::endl;
            return ;
        }
        std::vector<pollfd>::iterator it = pollfds.begin();
        while (it != pollfds.end()) {
            // if the data is available to read on the fd/socket
            // -> if the connection is new, accept it and add it to the pollfds
            // -> if the connection already exists, read the data and parse it
            if (it->revents && POLLIN) {
                if (it->fd == _serverSocketFd) {
                    int clientSocketFd = acceptSocket(_serverSocketFd);
                    if (clientSocketFd == -1) {
                        continue;
                    }
                    if (pollfds.size() < MAX_SOCKETS) {
                        addClient(clientSocketFd, newPollfds);
                    } else handleMaxClient(clientSocketFd);
                    it++;
                }
                // -> if the connection already exists, read the data and parse it
                else {
                    char buffer[BUFF_SIZE];
                    int readResult = recv(it->fd, buffer, BUFF_SIZE, 0);

                    if (readResult < 0) {
                        std::cerr << COLOR("Error: socket reading failed: ", RED) << strerror(errno) << std::endl;
                        deleteClient(pollfds, it->fd);
                        if (pollfds.size() == 0) {
                            std::cout << COLOR("No more clients connected. Exiting...", CYAN) << std::endl;
                            break ;
                        }
                    } else if (readResult == 0) {
                        deleteClient(pollfds, it->fd);
                        if (pollfds.size() == 0) {
                            std::cout << COLOR("No more clients connected. Exiting...", CYAN) << std::endl;
                            break ;
                        }
                    } else {
                        std::cout << COLOR("Received: ", CYAN) << buffer << std::endl;
                        // TODO: parse the request according to IRC protocol

                        // parse the request according to IRC protocol
                        // Respond to the request
                        // Handle errors and disconnections
                        // Close the socket
                        
                        parseMessage(buffer, it->fd);
                        it++;
                    }
                }
            }
            else if (it->revents & POLLERR) {
                if (it->fd == _serverSocketFd) {
                    std::cerr << COLOR("Error: server socket error: ", RED) << strerror(errno) << std::endl;
                    return ;
                } else {
                    std::cerr << COLOR("Error: client socket error: ", RED) << strerror(errno) << std::endl;
                    deleteClient(pollfds, it->fd);
                    if (pollfds.size() == 0) {
                        std::cout << COLOR("No more clients connected. Exiting...", CYAN) << std::endl;
                        break ;
                    }
                }
            } else {
                it++;
            }
        }
        // add new pollfds to the pollfds vector
        pollfds.insert(pollfds.end(), newPollfds.begin(), newPollfds.end());
    }
    return ;
}
     
