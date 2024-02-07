/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorin <kmorin@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 13:58:32 by kmorin            #+#    #+#             */
/*   Updated: 2024/02/07 16:00:53 by kmorin           ###   ########.fr       */
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
	t = true;
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

bool	Channel::getT() const {
	return (t);
}

const std::map<int, Client *>&	Channel::getClients() const {
	return (_clients);
}

Client *Channel::getClient(std::string nickname) {
	for (std::map<int, Client*>::iterator it = _clients.begin(); it != _clients.end(); ++it) {
		if (it->second->getNick() == nickname)
			return (it->second);
	}
	return (NULL);
}

std::map<int, Client*>::iterator Channel::getClientIt(std::string nickname) {
	std::map<int, Client*>::iterator it = _clients.begin();
	for (; it != _clients.end(); ++it) {
		if (it->second->getNick() == nickname)
			return (it);
	}
	return (it);
}

bool Channel::getInvitedClient(int fd) const {
	for (std::vector<int>::const_iterator it = _invitedClient.begin(); it != _invitedClient.end(); it++) {
		if (*it == fd)
			return (true);
	}
	return (false);
}

bool Channel::isClientInChannel(int fd) const {
	std::map<int, Client *>::const_iterator it = _clients.find(fd);
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

void	Channel::setT(bool status) {
	t = status;
}

void Channel::setInvitedClient(int fd) {
	_invitedClient.push_back(fd);
}

/* ************************************************************************** */
/*                               CHANNEL METHODS                              */
/* ************************************************************************** */

void Channel::addClient(Client *client) {

	// std::cout << "added client " << client->getNick() << " in channel " << getName() << std::endl;
	_clients.insert(std::pair<int, Client *>(client->getFd(), client));
}

void Channel::removeClient(Client *client) {
	client->setCurrentChannel("");
	_clients.erase(client->getFd());
}

void Channel::sendMessageToAllClients(std::string &message, int flag) {

	std::string msg = message;
	std::map<int, Client *>::const_iterator it = _clients.begin();
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
	std::map<int, Client *>::const_iterator it = _clients.begin();
	while (it != _clients.end()) {
		if (it->second != client)
			it->second->sendMessage(msg, 0);
		it++;
	}
	std::cout << COLOR("Sending message to all clients in channel ", CYAN) << _name << std::endl;
	std::cout << COLOR("Message: ", CYAN) << message << std::endl;
}

void Channel::deleteInvitedClient(int fd) {
	_invitedClient.erase(std::remove(_invitedClient.begin(), _invitedClient.end(), fd));
}

void Channel::removeClientFromChannel(int fd) {
	_clients.erase(fd);
}
