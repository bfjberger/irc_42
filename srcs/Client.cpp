/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorin <kmorin@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 17:03:17 by pvong             #+#    #+#             */
/*   Updated: 2024/02/06 23:26:56 by kmorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

/* -------------------------------------------------------------------------- */
/*                                   CLIENT                                   */
/* -------------------------------------------------------------------------- */

Client::Client(int fd, std::string address) : _fd(fd), _address(address),
														_receivedInfo(false),
														_isLogged(false),
														_welcomeSent(false),
														_isRegistered(false),
														_isInChannel(false),
														_isOperator(false),
														_deconnection(false),
														_hostname("localhost"),
														_currentChannel(""),
														_maxChannels(5) {
	return;
}

Client::~Client() {
	return;
}

/* --------------------------------- Getters -------------------------------- */

int	Client::getFd() const {
	return (_fd);
}

const std::string&	Client::getAddress() const {
	return (_address);
}

bool	Client::hasReceivedInfo() const {
	return (_receivedInfo);
}

bool	Client::isLogged() const {
	return (_isLogged);
}

bool	Client::welcomeSent() const {
	return (_welcomeSent);
}

bool	Client::isRegistered() const {
	return (_isRegistered);
}

bool	Client::isInChannel() const {
	return (_isInChannel);
}

bool	Client::isOperator() const {
	return (_isOperator);
}

bool	Client::isOperator(Channel* chan) const {
	std::map<Channel*, bool>::const_iterator	it = _channels.find(chan);

	if (it == _channels.end()) {
		return (false);
	}
	return (it->second);
}

bool	Client::getDeconnection() const {
	return (_deconnection);
}

const std::string&	Client::getNick() const {
	return (_nick);
}

const std::string&	Client::getUserName() const {
	return (_userName);
}

const std::string&	Client::getPass() const {
	return (_password);
}

const std::string&	Client::getHostname() const {
	return (_hostname);
}

const std::string&	Client::getCurrentChannel() const {
	return (_currentChannel);
}

const int&	Client::getMaxChannels() const {
	return (_maxChannels);
}

Client*	Client::getClientByFd(Server* server, int clientFd) {
	std::map<int, Client*> clientsList = server->getClients();
	Client* client = NULL;

	try {
		client = clientsList.at(clientFd);
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
	return (client);
}

const std::map<Channel*, bool>&	Client::getChannels() const {
	return (_channels);
}

std::map<Channel*, bool>::iterator	Client::getChannel(std::string channelName) {
	std::map<Channel*, bool>::iterator	it = _channels.begin();
	for (; it != _channels.end(); ++it) {
		if (it->first->getName() == channelName)
			break;
	}
	return (it);
}

/* --------------------------------- Setters -------------------------------- */

void	Client::setLogged(bool isLogged) {
	_isLogged = isLogged;
}

void	Client::setReceivedInfo(bool receivedInfo) {
	_receivedInfo = receivedInfo;
}

void	Client::setWelcomeSent(bool welcomeSent) {
	_welcomeSent = welcomeSent;
}

void	Client::setRegistered(bool isRegistered) {
	_isRegistered = isRegistered;
}

void	Client::setInChannel(bool inChannel) {
	_isInChannel = inChannel;
}

void	Client::setOperator(bool isOperator) {
	_isOperator = isOperator;
}

void	Client::setNick(std::string nick) {
	_nick = nick;
}

void	Client::setUserName(std::string userName) {
	_userName = userName;
}

void	Client::setPass(std::string pass) {
	_password = pass;
}

void	Client::setHostname(std::string hostname) {
	_hostname = hostname;
}

void	Client::setCurrentChannel(std::string channel) {
	_currentChannel = channel;
}

void	Client::setDeconnection(bool deconnection) {
	_deconnection = deconnection;
}

/* ----------------------------- Client methods ----------------------------- */

void	Client::sendMessage(std::string& message, int showMsg) {
	if (showMsg == SHOW_MSG) {
		std::cout << COLOR("Sending message to client ", CYAN) << _fd;
		std::cout << COLOR(" >> ", CYAN) << message << std::endl;
	}
	if (message.find("\r\n") == std::string::npos)
		message += "\r\n";
	send(_fd, message.c_str(), message.length(), 0);
}

void	Client::addChannel(Channel* chan, bool chanOp) {

	_channels.insert(std::pair<Channel*, bool>(chan, chanOp));
}

void	Client::removeChannel(Channel* chan) {

	_channels.erase(chan);
}

void	Client::changeOpStatus(Channel* chan, bool chanOp, Client* client) {

	std::map<Channel*, bool>::iterator	it = getChannel(chan->getName());

	if (it == _channels.end()) {
		std::string	response = "Couldn't find the channel in the ones where the client is.\r\n";
		send(client->getFd(), response.c_str(), response.size(), 0);
	}
	else {
		removeChannel(chan);
		addChannel(chan, chanOp);
	}
}

/* --------------------------------- Helpers -------------------------------- */

void Client::printInfo() const {
	std::cout << "----------------------------------------" << std::endl;
	std::cout << "Client info:" << std::endl;
	std::cout << "   fd: " << _fd << std::endl;
	std::cout << "   nick: " << _nick << std::endl;
	std::cout << "   userName: " << _userName << std::endl;
	std::cout << "   password: " << _password << std::endl;
	std::cout << "   currentChannel: " << _currentChannel << std::endl;
	std::cout << "   receivedInfo: " << std::boolalpha << _receivedInfo << std::endl;
	std::cout << "   isLogged: " << std::boolalpha << _isLogged << std::endl;
	std::cout << "   isRegistered: " << std::boolalpha << _isRegistered << std::endl;
	std::cout << "   isInChannel: " << std::boolalpha << _isInChannel << std::endl;
	std::cout << "----------------------------------------" << std::endl;
}
