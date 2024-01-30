/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorin <kmorin@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 13:58:32 by kmorin            #+#    #+#             */
/*   Updated: 2024/01/30 10:47:00 by kmorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

/* ************************************************************************** */
/*                          CONSTRUCTOR - DESTRUCTOR                          */
/* ************************************************************************** */

Channel::Channel(const std::string& name) {

	_name = name;
	_topic = "";
	_password = "";
	_userLimit = -1;
	i = false;
	// t = false;
	k = false;
	// o = false;
	l = false;
}

Channel::~Channel(void) {

	// std::map<std::string, Client*>::const_iterator it = _clients.begin();
	// while (it != _clients.end()) {
	// 	// it->second->setCurrentChannel("");
	// 	// _clients.erase(it);
	// 	it++;
	// }

}

/* ************************************************************************** */
/*                                   GETTERS                                  */
/* ************************************************************************** */

std::string	Channel::getName(void) const {
	return (_name);
}

std::string	Channel::getTopic(void) const {
	return (_topic);
}

std::string	Channel::getPassword(void) const {
	return (_password);
}

int	Channel::getUserLimit() const {
	return (_userLimit);
}

bool	Channel::getI() const {
	return (i);
}

// bool	Channel::getT() const {
// 	return (t);
// }

bool	Channel::getK() const {
	return (k);
}

// bool	Channel::getO() const {
// 	return (o);
// }

bool	Channel::getL() const {
	return (l);
}

const std::map<std::string, Client*>&	Channel::getClients() const {
	return (_clients);
}

Client*	Channel::getClient(std::string clientName) {
	std::map<std::string, Client*>::iterator it = this->_clients.find(clientName);
	if (it != this->_clients.end())
		return (it->second);
	return (NULL);
}

/* ************************************************************************** */
/*                                   SETTERS                                  */
/* ************************************************************************** */

void	Channel::setName(std::string name) {
	_name = name;
}

void	Channel::setTopic(std::string topic) {
	_topic = topic;
}

void	Channel::setPassword(std::string password) {
	_password = password;
}

void	Channel::setUserLimit(int i) {
	_userLimit = i;
}

void	Channel::setI(bool status) {
	i = status;
}

// void	Channel::setT(bool status) {
// 	t = status;
// }

void	Channel::setK(bool status) {
	k = status;
}

// void	Channel::setO(bool status) {
// 	o = status;
// }

void	Channel::setL(bool status) {
	l = status;
}

/* ************************************************************************** */
/*                               CHANNEL METHODS                              */
/* ************************************************************************** */

void	Channel::addClient(Client* client) {

	_clients.insert(std::pair<std::string, Client*>(client->getNick(), client));
}

void	Channel::removeClient(Client* client) {
	client->setCurrentChannel("");
	_clients.erase(client->getNick());
}

void	Channel::sendMessageToAllClients(std::string& message) {

	std::map<std::string, Client*>::const_iterator it = _clients.begin();
	while (it != _clients.end()) {
		it->second->sendMessage(message);
		it++;
	}
}

void	Channel::sendToAllButOne(std::string& message, Client* client){

	std::map<std::string, Client*>::const_iterator it = _clients.begin();
	while (it != _clients.end()) {
		if (it->second != client)
			it->second->sendMessage(message);
		it++;
	}
	std::cout << COLOR("Sending message to all clients in channel ", CYAN) << _name << std::endl;
	std::cout << COLOR("Message: ", CYAN) << message << std::endl;
}
