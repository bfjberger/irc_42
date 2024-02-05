/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Kill.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorin <kmorin@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:36:01 by kmorin            #+#    #+#             */
/*   Updated: 2024/01/29 12:49:37 by kmorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Commands/Kill.hpp"

Kill::Kill(void) {}

Kill::~Kill(void) {}

/**
 * https://datatracker.ietf.org/doc/html/rfc2812#section-3.7.1
 *
 * Parameters:
 * 		<nickname> <comment>
 *
 * If the number of parameters is not valid, the corresponding error message is sent to the client.
 * If the client is not an operator, the corresponding error message is sent to the client.
 * If the nickname of the client to be killed is not found, the corresponding error message is sent to the client.
 * Else, the client receive a message explaining why he has been killed and the server closes the connection.
 *
 * @param server The server Object.
 * @param msg The message object containing the command and parameters.
 * @param client The client object.
*/
void	Kill::execute(Server* server, t_Message* msg, Client* client) {

	if (msg->params.size() < 2) {
		std::string	errNeedMoreParams = ERR_NEEDMOREPARAMS(client->getNick(), msg->command);
		client->sendMessage(errNeedMoreParams);
		return;
	}
	else if (!client->isOperator()) {
		std::string	errNoPrivileges = ERR_NOPRIVILEGES(client->getNick());
		client->sendMessage(errNoPrivileges);
		return;
	}

	std::map<int, Client*>	clients = server->getClients();

	std::map<int, Client*>::const_iterator it;
	for (it = clients.begin(); it != clients.end(); ++it) {
		if (it->second->getNick() == msg->params[0])
			break;
	}

	if (it == clients.end()) {
		std::string	errNoSuchNick = ERR_NOSUCHNICK(client->getNick(), msg->params[0]);
		client->sendMessage(errNoSuchNick);
	}
	else {
		std::string	params;
		for (std::vector<std::string>::iterator it = msg->params.begin() + 1; it != msg->params.end(); it++) {
			params += *it;
			if (it + 1 != msg->params.end())
				params += " ";
		}
		std::string	rplKill = "You were removed from the server because " + params + "\r\n";
		it->second->sendMessage(rplKill);

		close(it->second->getFd());
	}
}
