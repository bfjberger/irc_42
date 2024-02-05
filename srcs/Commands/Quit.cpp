/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorin <kmorin@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:36:10 by kmorin            #+#    #+#             */
/*   Updated: 2024/02/05 14:18:18 by kmorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Commands/Quit.hpp"

Quit::Quit(void) {}

Quit::~Quit(void) {}

/**
 * https://datatracker.ietf.org/doc/html/rfc2812#section-3.1.7
 *
 * Parameter:
 * 		[ <quit message> ]
 *
 * If no parameter is passed, the default quit message is send by the client.
 * If a parameter is passed, it's content is added to the message send by the client.
 * 	before the server close the connection between him and the client.
 *
 * @param server The server object.
 * @param msg The message object containing the command and parameters.
 * @param client The client object.
*/
void	Quit::execute(Server* server, t_Message* msg, Client* client) {

	(void) server;

	std::string	quitMsg = client->getNick() + " [" + client->getHostname() + "] has quit [Quit: ";

	if (msg->params.empty()) {
		quitMsg += "leaving]\n\r";
		client->sendMessage(quitMsg);
	}
	else {
		std::string	params = getParams(msg, 0);

		quitMsg += params + "]\n\r";
		client->sendMessage(quitMsg);
	}

	std::map<Channel*, bool>::iterator	it = client->getChannel(client->getCurrentChannel());
	if (it != client->getChannels().end()) {
		std::string	params = getParams(msg, 0);
		if (params.empty() == false && params[0] == ':')
			params.erase(0, 1);
		std::string channelQuit = ":" + USER_ID(client) + " QUIT :Quit: " + params;
		it->first->sendMessageToAllClients(channelQuit);
	}

	close(client->getFd());
}
