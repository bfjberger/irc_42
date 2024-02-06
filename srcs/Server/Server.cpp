/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorin <kmorin@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 13:49:00 by pvong             #+#    #+#             */
/*   Updated: 2024/02/06 14:15:33 by kmorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

/* -------------------------------------------------------------------------- */
/*                               STRUCT MESSAGE                               */
/* -------------------------------------------------------------------------- */

std::string getParams(t_Message* msg, int index) {

	std::string params;

	if (index < 0)
		return (params);
	else if (index >= (int)msg->params.size())
		return (params);

	for (size_t i = index; i < msg->params.size(); i++) {
		params += msg->params[i];
		if (i < msg->params.size() - 1)
			params += " ";
	}
	return (params);
}

/* -------------------------------------------------------------------------- */
/*                           CONSTRUCTOR/DESTRUCTOR                           */
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
 *
 * version -> version of the server
 * name -> name of the server
 * initialization of the map stocking an instance of all available commands
 * call the launch method that will start the server
 */
Server::Server(const std::string port, const std::string password) : _port(port), _password(password) {

	_name = "SERVER-BPHK";
	_version = "alpha";

	_commands["INVITE"] = new Invite();
	_commands["JOIN"] = new Join();
	_commands["KICK"] = new Kick();
	_commands["KILL"] = new Kill();
	_commands["MODE"] = new Mode();
	_commands["NICK"] = new Nick();
	_commands["OPER"] = new Oper();
	_commands["PART"] = new Part();
	_commands["PASS"] = new Pass();
	_commands["PRIVMSG"] = new Privmsg();
	_commands["QUIT"] = new Quit();
	_commands["TOPIC"] = new Topic();
	_commands["USER"] = new User();

	Server::launch();
}

Server::~Server() {

	std::cout << COLOR("Closing server socket...", CYAN) << std::endl;

	close(_serverSocketFd);

	for (std::map<std::string, ACommand*>::iterator it = _commands.begin(); it != _commands.end(); ++it) {
		delete it->second;
		// _commands.erase(it);
	}

	for (std::map<int, Client*>::iterator it = _clients.begin(); it != _clients.end(); ++it) {
		close(it->first);
		delete it->second;
		// _clients.erase(it);
	}

	for (std::map<std::string, Channel*>::iterator it = _channels.begin(); it != _channels.end(); ++it) {
		delete it->second;
		// _channels.erase(it);
	}

	close(_bot.first);
	delete _bot.second;
}

/* -------------------------------------------------------------------------- */
/*                             SERVER MANAGEMENT                              */
/* -------------------------------------------------------------------------- */

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

void	Server::launch() {

	_serverSocketFd = socket(AF_INET, SOCK_STREAM, 0);

	if (_serverSocketFd < 0) {
		std::cerr << COLOR("Error: socket creation failed.", RED) << std::endl;
		exit(EXIT_FAILURE);
	}

	_serverAddress.sin_family = AF_INET;					  // IPv4
	_serverAddress.sin_addr.s_addr = INADDR_ANY;			  // bind to all available interfaces
	_serverAddress.sin_port = htons(std::atoi(_port.c_str())); // convert port to int and convert to network byte order

	int optValue = 1;
	if (setsockopt(_serverSocketFd, SOL_SOCKET, SO_REUSEPORT, &optValue, sizeof(optValue)) < 0) {
		std::cerr << COLOR("Error: socket option SO_REUSEPORT failed: ", RED) << strerror(errno) << std::endl;
		close(_serverSocketFd);
		exit(EXIT_FAILURE);
	}

	int bindResult = bind(_serverSocketFd, (struct sockaddr *)&_serverAddress, sizeof(_serverAddress));
	if (bindResult < 0) {
		std::cerr << COLOR("Error: socket binding failed: ", RED) << strerror(errno) << std::endl;
		close(_serverSocketFd);
		exit(EXIT_FAILURE);
	}

	if (listen(_serverSocketFd, MAX_SOCKETS) < 0) {
		std::cerr << COLOR("Error: socket listening failed: ", RED) << strerror(errno) << std::endl;
		close(_serverSocketFd);
		exit(EXIT_FAILURE);
	}

	//BOT HANDLING
	int	botSocket = socket(AF_INET, SOCK_STREAM, 0);

	Bot* bot = new Bot(botSocket);

	struct sockaddr_in	botAddress = bot->getBotAddress();

	if (botSocket < 0) {
		std::cerr << COLOR("Error: bot socket creation failed.", RED) << std::endl;
		exit(EXIT_FAILURE);
	}

	botAddress.sin_family = AF_INET;					  // IPv4
	botAddress.sin_addr.s_addr = INADDR_ANY;			  // bind to all available interfaces
	botAddress.sin_port = htons(std::atoi(_port.c_str())); // convert port to int and convert to network byte order

	int optValue2 = 1;
	if (setsockopt(botSocket, SOL_SOCKET, SO_REUSEPORT, &optValue2, sizeof(optValue2)) < 0) {
		std::cerr << COLOR("Error: bot socket option SO_REUSEPORT failed: ", RED) << strerror(errno) << std::endl;
		close(botSocket);
		exit(EXIT_FAILURE);
	}

	int bindResult2 = bind(botSocket, (struct sockaddr *)&botAddress, sizeof(botAddress));
	if (bindResult2 < 0) {
		std::cerr << COLOR("Error: bot socket binding failed: ", RED) << strerror(errno) << std::endl;
		close(botSocket);
		exit(EXIT_FAILURE);
	}

	if (listen(botSocket, MAX_SOCKETS) < 0) {
		std::cerr << COLOR("Error: bot socket listening failed: ", RED) << strerror(errno) << std::endl;
		close(botSocket);
		exit(EXIT_FAILURE);
	}

	_bot = std::pair<int, Bot*>(botSocket, bot);

	std::cout << COLOR("Added bot ", CYAN) << bot->getName() << COLOR(" on port ", CYAN) << botSocket << std::endl;
	//BACK TO NORMAL

	std::cout << COLOR("Listening for connections on port ", CYAN) << _port << COLOR(" with password: ", CYAN) << _password << " ..." << std::endl;
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
int	Server::acceptSocket(int listenSocket) {

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

void	Server::handleMaxClient(int clientSocketFd) {

	std::cout << COLOR(ERR_MAX_CLIENTS, RED) << std::endl;

	send(clientSocketFd, ERR_MAX_CLIENTS, strlen(ERR_MAX_CLIENTS), 0);
	close(clientSocketFd);
}

int	Server::createClientConnection(std::vector<pollfd> &pollfds, std::vector<pollfd> &newPollfds) {

	int clientSocketFd = acceptSocket(_serverSocketFd);

	if (clientSocketFd == -1) {
		std::cout << COLOR("Error: socket accepting failed: ", RED) << strerror(errno) << std::endl;
		return (CONTINUE);
	}
	if (pollfds.size() - 1 < MAX_SOCKETS) {
		addClient(clientSocketFd, newPollfds);
	}
	else
		handleMaxClient(clientSocketFd);
	return (0);
}

int	Server::handleExistingConnection(std::vector<pollfd> &pollfds, std::vector<pollfd>::iterator it) {

	char buffer[BUFF_SIZE];
	int readResult;

	memset(buffer, 0, sizeof(buffer));
	readResult = recv(it->fd, buffer, BUFF_SIZE, 0);

	if (readResult < 0) {
		std::cerr << COLOR("Error: socket reading failed: ", RED) << strerror(errno) << std::endl;
		deleteClient(pollfds, it);
		return (BREAK);
	}
	else if (readResult == 0) {
		deleteClient(pollfds, it);
		std::cout << COLOR("[SERVER] A Client just disconnected.", YELLOW) << std::endl;
		return (BREAK);
	}
	else if (readResult > 100) {
		std::cout << COLOR("Buffer too long.", RED) << std::endl;
		return (CONTINUE);
	}
	else {
		// if the buffer last char is not a newline, we aggregate it (handle CTRL D case)
		if (buffer[readResult - 1] != '\n' && _aggMessagesStatus[it->fd] == false) {
			std::cout << "_aggMessagesStatus[" << it->fd << "] = " << _aggMessagesStatus[it->fd] << " : ";
			_aggMessagesStatus[it->fd] = true;
			_aggMessages[it->fd] += buffer;
			std::cout << _aggMessages[it->fd] << std::endl;
			return (0);
		} 
		// if the buffer last char is not a newline and we are already aggregating, we continue to aggregate
		else if (buffer[readResult - 1] != '\n' && _aggMessagesStatus[it->fd] == true) {
			std::cout << "_aggMessagesStatus[" << it->fd << "] = " << _aggMessagesStatus[it->fd] << " : ";
			_aggMessages[it->fd] += buffer;
			std::cout << _aggMessages[it->fd] << std::endl;
			return (0);
		} 
		// else the buffer is complete and we can parse it
		else if (_aggMessagesStatus[it->fd] == true) {
			_aggMessagesStatus[it->fd] = false;
			_aggMessages[it->fd] += buffer;
			std::string	tmp(_aggMessages[it->fd]);
			trimString(tmp);
			std::cout << COLOR("Received: ", CYAN) << "|" << tmp << "|" << std::endl;
			parser(_aggMessages[it->fd], it->fd);
			_aggMessages[it->fd] = "";
			return (0);
		}
		buffer[readResult] = '\0';
		std::string	tmp(buffer);
		trimString(tmp);
		std::cout << COLOR("Received: ", CYAN) << "|" << tmp << "|" << std::endl;
		parser(buffer, it->fd);
	}
	return (0);
}

int	Server::handlePollout(std::vector<pollfd> &pollfds, std::vector<pollfd>::iterator it) {

	Client* client = Client::getClientByFd(this, it->fd);
	if (client == NULL) {
		std::cout << COLOR("Error: client not found.", RED) << std::endl;
	}
	else {
		if (client->getDeconnection() == true) {
			deleteClient(pollfds, it);
			return (BREAK);
		}
	}
	return (0);
}

int	Server::handlePollErr(std::vector<pollfd> &pollfds, std::vector<pollfd>::iterator it) {

	if (it->fd == _serverSocketFd) {
		std::cerr << COLOR("Error: server socket error: ", RED) << strerror(errno) << std::endl;
		return (FAILURE);
	}
	else {
		deleteClient(pollfds, it);
		return (BREAK);
	}
	return (0);
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
 *
 * @note This function runs indefinitely until an error occurs or all clients disconnect.
 */
void	Server::run() {

	std::vector<pollfd> pollfds;
	pollfd serverPollfd;
	serverPollfd.fd = _serverSocketFd;
	serverPollfd.events = POLLIN;
	pollfds.push_back(serverPollfd);

	pollfd	botPollfd;

	botPollfd.fd = _bot.second->getFd();
	botPollfd.events = POLLIN;
	pollfds.push_back(botPollfd);

	while (g_server_running == true) {
		std::vector<pollfd> newPollfds;

		if (poll(&pollfds[0], pollfds.size(), -1) == -1) {
			if (g_server_running == false)
				return;
			std::cerr << COLOR("Error: poll failed: ", RED) << strerror(errno) << std::endl;
			return;
		}
		std::vector<pollfd>::iterator it = pollfds.begin();
		while (it != pollfds.end()) {
			if (it->revents & POLLIN) { // if the data is available to read on the fd/socket
				if (it->fd == _serverSocketFd) {
					if (createClientConnection(pollfds, newPollfds) == CONTINUE)
						continue;
				}
				else { // if the connection already exists, read the data and parse it
					if (handleExistingConnection(pollfds, it) == BREAK)
						break;
				}
			}
			else if (it->revents & POLLOUT) {
				// if the data is available to write on the fd/socket
				if (handlePollout(pollfds, it) == BREAK)
					break;
			}
			else if (it->revents & POLLERR) { // if an error occurred on the fd/socket
				if (handlePollErr(pollfds, it) == BREAK)
					break;
				else
					return;
			}
			it++;
		}
		// add new pollfds to the pollfds vector
		pollfds.insert(pollfds.end(), newPollfds.begin(), newPollfds.end());
	}
	return;
}

/* -------------------------------------------------------------------------- */
/*                                  GETTERS                                   */
/* -------------------------------------------------------------------------- */

std::string const &Server::getPass() const {
	return (_password);
}

const std::map<int, Client*>&	Server::getClients() const {
	return (_clients);
}

Client*	Server::getClient(std::string nickname) {
	std::map<int, Client*>::iterator it = this->_clients.begin();
	for (; it != this->_clients.end(); ++it) {
		if (it->second->getNick() == nickname)
			return (it->second);
	}
	return (NULL);
}

const std::map<std::string, Channel*>&	Server::getChannels() const {
	return (_channels);
}

Channel*	Server::getChannel(std::string channelName) {
	std::map<std::string, Channel*>::iterator it = _channels.find(channelName);
	if (it != this->_channels.end())
		return (it->second);
	return (NULL);
}

Bot*	Server::getBot() const {
	return (_bot.second);
}

/* -------------------------------------------------------------------------- */
/*                              CLIENT MANAGEMENT                             */
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
void	Server::deleteClient(std::vector<pollfd> &pollfds, std::vector<pollfd>::iterator it) {

	std::cout << COLOR("Client ", CYAN) << it->fd << COLOR(" disconnected.", CYAN) << std::endl;

	std::map<int, Client*>::iterator	client = this->_clients.find(it->fd);
	delete client->second;
	this->_clients.erase(client);

	close(it->fd);

	pollfds.erase(it);

	std::cout << COLOR("Number of clients: ", CYAN) << pollfds.size() - 2 << std::endl; // -2 because of the bot and the server fds
}

void	Server::addClient(int clientSocket, std::vector<pollfd> &pollfds) {

	pollfd				clientPollfd;
	std::string			strClientAddress;
	struct sockaddr_in	clientAddress;
	socklen_t			clientAddressSize = sizeof(clientAddress);

	if (getsockname(clientSocket, (struct sockaddr *)&clientAddress, &clientAddressSize) == -1) {
		std::cerr << COLOR("Error: getting socket information failed: ", RED) << strerror(errno) << std::endl;
		strClientAddress = "127.0.0.1";
		std::cerr << COLOR("Assigned the localhost address as default: ", RED) << strClientAddress << std::endl;
	}
	else
		strClientAddress = inet_ntoa(clientAddress.sin_addr);

	Client*	client = new Client(clientSocket, strClientAddress);

	clientPollfd.fd = clientSocket;
	clientPollfd.events = POLLIN | POLLOUT; // data can be read and written
	pollfds.push_back(clientPollfd);
	_clients.insert(std::pair<int, Client *>(clientSocket, client));
	_aggMessagesStatus.insert(std::pair<int, bool>(clientSocket, false));
	_aggMessages.insert(std::pair<int, std::string>(clientSocket, ""));

	std::cout << COLOR("Added client #", CYAN) << clientSocket << std::endl;
}

bool	Server::isNick(std::string nick) {
	std::map<int, Client*>::iterator it = this->_clients.begin();
	while (it != this->_clients.end()) {
		if (it->second->getNick() == nick)
			return (true);
		it++;
	}
	return (false);
}

/* -------------------------------------------------------------------------- */
/*                             CHANNEL MANAGEMENT                             */
/* -------------------------------------------------------------------------- */

bool	Server::isChannel(std::string channelName) {
	std::map<std::string, Channel*>::iterator it = this->_channels.find(channelName);
	if (it != this->_channels.end())
		return (true);
	return (false);
}

void	Server::addChannel(Channel* channel) {
	this->_channels.insert(std::pair<std::string, Channel*>(channel->getName(), channel));
}

void	Server::removeChannel(std::string channelName) {
	delete this->_channels[channelName];
	this->_channels.erase(channelName);
}
