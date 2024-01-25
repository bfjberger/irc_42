/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorin <kmorin@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:36:10 by kmorin            #+#    #+#             */
/*   Updated: 2024/01/25 10:08:59 by kmorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Commands/Quit.hpp"

Quit::Quit(void) {}

Quit::~Quit(void) {}

/*
Excepting ->
	(with one param)
		kikinoxx [~kmorin@67ad-8ab6-b0a4-3ff5-ce28.25.185.ip] has quit [Quit: aurevoir]
	(with multiple param)
		kikinoxx [~kmorin@67ad-8ab6-b0a4-3ff5-ce28.25.185.ip] has quit [Quit: goodbye old friend may the force be with you]
	(with no param)
		kikinoxx [~kmorin@67ad-8ab6-b0a4-3ff5-ce28.25.185.ip] has quit [Quit: leaving]

Ours ->
	(with one param)
		k [localhost] has quit [Quit: aurevoir]

	(with multiple param)
		k [localhost] has quit [Quit: goodbye old friend may the force be with you]

	(with no param)
		k [localhost] has quit [Quit: leaving]
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
