/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvong <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 17:03:17 by pvong             #+#    #+#             */
/*   Updated: 2024/01/18 17:53:28 by pvong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

/* -------------------------------------------------------------------------- */
/*                                   CLIENT                                   */
/* -------------------------------------------------------------------------- */

Client::Client(int fd) : _fd(fd), _isLogged(false) {
    return ;
}

Client::~Client() {
    return ;
}

/* --------------------------------- Getters -------------------------------- */

bool Client::hasReceivedInfo() const {
    return _receivedInfo;
}

int Client::getFd() const {
    return _fd;
}

std::string Client::getNick() const {
    return _nick;
}

std::string Client::getUserName() const {
    return _userName;
}

std::string Client::getRealName() const {
    return _realName;
}

bool Client::isLogged() const {
    return _isLogged;
}

/* --------------------------------- Setters -------------------------------- */

void Client::setNick(std::string nick) {
    _nick = nick;
}

void Client::setUserName(std::string userName) {
    _userName = userName;
}

void Client::setRealName(std::string realName) {
    _realName = realName;
}

void Client::setLogged(bool isLogged) {
    _isLogged = isLogged;
}

void Client::setReceivedInfo(bool receivedInfo) {
    _receivedInfo = receivedInfo;
}

/* --------------------------------- Helpers -------------------------------- */

void Client::printInfo() const {
    std::cout << "Client info:" << std::endl;
    std::cout << "fd: " << _fd << std::endl;
    std::cout << "nick: " << _nick << std::endl;
    std::cout << "userName: " << _userName << std::endl;
    std::cout << "realName: " << _realName << std::endl;
    std::cout << "receivedInfo: " << _receivedInfo << std::endl;
    std::cout << "isLogged: " << _isLogged << std::endl;
}