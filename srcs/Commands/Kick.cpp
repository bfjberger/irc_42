/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorin <kmorin@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:36:00 by kmorin            #+#    #+#             */
/*   Updated: 2024/01/29 16:12:07 by kmorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Commands/Kick.hpp"

Kick::Kick(void) {}

Kick::~Kick(void) {}

void	Kick::execute(Server* server, t_Message* msg, Client* client) {

	std::string	nameChannel = msg->params[0];

	Channel*	tmp = server->getChannel(nameChannel);

	if (!tmp) {
		// ERR_NOSUCHCHANNEL
	}

	std::map<Channel*, bool>	other = client->getChannels();
	std::map<Channel*, bool>::iterator it = other.find(tmp);

	if (it->second == false) {
		// ERR_CHANOPRIVSNEEDED
	}

	std::map<std::string, Client*>	clientsList = tmp->getClients();
	for (std::map<std::string, Client*>::iterator it = clientsList.begin(); it != clientsList.end(); ++it) {
		if (it->first == msg->params[1])
			break;
	}

	//check for the client to be kicked
}
