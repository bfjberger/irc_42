/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorin <kmorin@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:36:10 by kmorin            #+#    #+#             */
/*   Updated: 2024/01/26 15:28:12 by kmorin           ###   ########.fr       */
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
		send(client->getFd(), quitMsg.c_str(), quitMsg.size(), 0);

		close(client->getFd());
	}
	else {
		std::string	params;
		for (std::vector<std::string>::iterator it = msg->params.begin(); it != msg->params.end(); it++) {
			params += *it;
			if (it + 1 != msg->params.end())
				params += " ";
		}

		quitMsg += params + "]\n\r";
		send(client->getFd(), quitMsg.c_str(), quitMsg.size(), 0);

		close(client->getFd());
	}
}
