/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorin <kmorin@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:36:02 by kmorin            #+#    #+#             */
/*   Updated: 2024/01/26 17:20:28 by kmorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Commands/Mode.hpp"

Mode::Mode(void) {}

Mode::~Mode(void) {}

/**
 * https://datatracker.ietf.org/doc/html/rfc2812#section-3.1.5 User MODE
 * https://datatracker.ietf.org/doc/html/rfc2812#section-3.2.3 Channel MODE
 *
 * Parameters:
 * 		<nickname> {[+|-]|o}
 *
 * @param server The server object.
 * @param msg The message object containing the command and parameters.
 * @param client The client object.
*/
void	Mode::execute(Server* server, t_Message* msg, Client* client) {

	(void) server;

	if (msg->params.size() < 1) {
		std::string	tmp = ERR_NEEDMOREPARAMS(client->getNick(), msg->command);
		send(client->getFd(), tmp.c_str(), tmp.size(), 0);
		return;
	}

	/*
		USER MODE
	*/
	std::map<int, Client*>	clients = server->getClients();

	std::map<int, Client*>::const_iterator it;
	for (it = clients.begin(); it != clients.end(); ++it) {
		if (it->second->getNick() == msg->params[0])
			break;
	}

	if (it == clients.end()) {
		std::string	tmp = ERR_USERSDONTMATCH(client->getNick());
		send(client->getFd(), tmp.c_str(), tmp.size(), 0);
	}
	else if (msg->params.size() == 1) {
		std::string	tmp;
		if (client->isOperator())
			tmp = RPL_UMODEIS(client->getNick(), "+o");
		else
			tmp = RPL_UMODEIS(client->getNick(), "-o");
		send(client->getFd(), tmp.c_str(), tmp.size(), 0);
	}
	else if (!msg->params[1].compare("+o")) {
		//ignore
	}
	else if (!msg->params[1].compare("-o")) {
		std::string	tmp;
		if (client->isOperator()) {
			client->setOperator(false);
			tmp = "You're now no longer an operator !\r\n";
		}
		else
			tmp = "lol from the start you're not an operator !\r\n";
		send(client->getFd(), tmp.c_str(), tmp.size(), 0);
	}
	else {
		std::string	tmp = ERR_UMODEUNKNOWNFLAG(client->getNick());
		send(client->getFd(), tmp.c_str(), tmp.size(), 0);
	}
}
