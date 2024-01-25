/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorin <kmorin@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 17:03:17 by pvong             #+#    #+#             */
/*   Updated: 2024/01/25 14:04:54 by kmorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

/* -------------------------------------------------------------------------- */
/*                                   CLIENT                                   */
/* -------------------------------------------------------------------------- */

Client::Client(int fd) : _fd(fd),
						_receivedInfo(false),
						_isLogged(false),
						_welcomeSent(false),
						_isRegistered(false),
						_isInChannel(false),
						_hostname("localhost") {
	return;
}

Client::~Client() {
	return;
}

/* --------------------------------- Getters -------------------------------- */

int	Client::getFd() const {
	return _fd;
}

bool	Client::hasReceivedInfo() const {
	return _receivedInfo;
}

bool	Client::isLogged() const {
	return _isLogged;
}

bool	Client::welcomeSent() const {
	return _welcomeSent;
}

bool	Client::isRegistered() const {
	return _isRegistered;
}

bool	Client::isInChannel(void) const {
	return (_isInChannel);
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

/* --------------------------------- Helpers -------------------------------- */

void Client::printInfo() const {
	std::cout << "----------------------------------------" << std::endl;
	std::cout << "Client info:" << std::endl;
	std::cout << "fd: " << _fd << std::endl;
	std::cout << "nick: " << _nick << std::endl;
	std::cout << "userName: " << _userName << std::endl;
	std::cout << "password: " << _password << std::endl;
	std::cout << "receivedInfo: " << std::boolalpha << _receivedInfo << std::endl;
	std::cout << "isLogged: " << std::boolalpha << _isLogged << std::endl;
	std::cout << "----------------------------------------" << std::endl;
}
