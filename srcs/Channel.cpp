/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorin <kmorin@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 13:58:32 by kmorin            #+#    #+#             */
/*   Updated: 2024/01/30 11:53:54 by kmorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

/* ************************************************************************** */
/*                          CONSTRUCTOR - DESTRUCTOR                          */
/* ************************************************************************** */

Channel::Channel(const std::string &name) {

	_name = name;
	_topic = "";
	_password = "";
	_userLimit = -1;
	i = false;
	k = false;
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

std::string Channel::getName(void) const {
	return (_name);
}

std::string Channel::getTopic(void) const {
	return (_topic);
}

std::string Channel::getPassword(void) const {
	return (_password);
}

int Channel::getUserLimit() const {
	return (_userLimit);
}

bool Channel::getI() const {
	return (i);
}

bool Channel::getK() const {
	return (k);
}

bool Channel::getL() const {
	return (l);
}

const std::map<std::string, Client *> &Channel::getClients() const {
	return (_clients);
}

Client *Channel::getClient(std::string clientName) {
	std::map<std::string, Client *>::iterator it = this->_clients.find(clientName);
	if (it != this->_clients.end())
		return (it->second);
	return (NULL);
}

bool Channel::getInvitedClientVector(std::string ClientInvited) const {
	for (std::vector<std::string>::const_iterator it = invitedClientVector.begin(); it != invitedClientVector.end(); it++) {
		if (!it->compare(ClientInvited))
			return (true);
	}
	return (false);
}

bool Channel::isClientInChannel(std::string clientName) const {
	std::map<std::string, Client *>::const_iterator it = _clients.find(clientName);
	if (it != _clients.end())
		return (true);
	return (false);
}

/* ************************************************************************** */
/*                                   SETTERS                                  */
/* ************************************************************************** */

void Channel::setName(std::string name) {
	_name = name;
}

void Channel::setTopic(std::string topic) {
	_topic = topic;
}

void Channel::setPassword(std::string password) {
	_password = password;
}

void Channel::setUserLimit(int i) {
	_userLimit = i;
}

void Channel::setI(bool status) {
	i = status;
}

void Channel::setK(bool status) {
	k = status;
}

void Channel::setL(bool status) {
	l = status;
}

void Channel::setInvitedClientVector(std::string clientInvited) {
	invitedClientVector.push_back(clientInvited);
}

/* ************************************************************************** */
/*                               CHANNEL METHODS                              */
/* ************************************************************************** */

void Channel::addClient(Client *client) {

	_clients.insert(std::pair<std::string, Client *>(client->getNick(), client));
}

void Channel::removeClient(Client *client) {
	client->setCurrentChannel("");
	_clients.erase(client->getNick());
}

void Channel::sendMessageToAllClients(std::string &message, int flag) {

	std::string msg = message;
	std::map<std::string, Client *>::const_iterator it = _clients.begin();
	while (it != _clients.end()) {
		it->second->sendMessage(msg, flag);
		it++;
	}
	trimString(msg);
	std::cout << COLOR("Sending message to all clients in channel ", CYAN) << _name << std::endl;
	std::cout << COLOR("Message: ", CYAN) << message << std::endl;
}

void Channel::sendToAllButOne(std::string &message, Client *client, int flag) {

	std::string msg = message;
	if (flag == ISINCHANNEL) {
		msg = ":" + client->getNick() + "!" + client->getUserName() + "@" + client->getHostname() + " " + message;
	}
	std::map<std::string, Client *>::const_iterator it = _clients.begin();
	while (it != _clients.end()) {
		if (it->second != client)
			it->second->sendMessage(msg, 0);
		it++;
	}
	std::cout << COLOR("Sending message to all clients in channel ", CYAN) << _name << std::endl;
	std::cout << COLOR("Message: ", CYAN) << message << std::endl;
}

void Channel::deleteInvitedClient(std::string invitedClient) {
	invitedClientVector.erase(std::remove(invitedClientVector.begin(), invitedClientVector.end(), invitedClient));
}
