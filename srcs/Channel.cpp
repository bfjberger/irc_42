/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorin <kmorin@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 13:58:32 by kmorin            #+#    #+#             */
/*   Updated: 2024/01/19 14:15:06 by kmorin           ###   ########.fr       */
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
	userLimit = -1;
	i = false;
	t = false;
	k = false;
	o = false;
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

/* ************************************************************************** */
/*                                   SETTERS                                  */
/* ************************************************************************** */

void	Channel::setName(std::string& name) {

	_name = name;
}

void	Channel::setTopic(std::string& topic) {

	_topic = topic;
}

void	Channel::setPassword(std::string& password) {

	_password = password;
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
