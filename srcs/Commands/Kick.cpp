/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorin <kmorin@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:36:00 by kmorin            #+#    #+#             */
/*   Updated: 2024/01/30 13:45:36 by kmorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Commands/Kick.hpp"

Kick::Kick(void) {}

Kick::~Kick(void) {}

void Kick::execute(Server *server, t_Message *msg, Client *client) {

	if (msg->params.size() < 2) {
		std::string errNeedMore = ERR_NEEDMOREPARAMS(client->getNick(), msg->command);
		send(client->getFd(), errNeedMore.c_str(), errNeedMore.size(), 0);
		return;
	}

	std::string nameChannel = msg->params[0];

	Channel *tmp = server->getChannel(nameChannel);

	if (!tmp) {
		std::string errNoSuchChannel = ERR_NOSUCHCHANNEL(client->getNick(), nameChannel);
		send(client->getFd(), errNoSuchChannel.c_str(), errNoSuchChannel.size(), 0);
		return;
	}
	std::map<Channel *, bool> other = client->getChannels();
	std::map<Channel *, bool>::iterator it = other.find(tmp);
	if (it == other.end()) {
		std::cout << COLOR("red", "ERROR: ") << "Client " << client->getNick() << " is not in channel " << nameChannel << std::endl;
		return;
	}
	if (it->second == false) {
		std::string errNotOperator = ERR_CHANOPRIVSNEEDED(client->getNick(), nameChannel);
		send(client->getFd(), errNotOperator.c_str(), errNotOperator.size(), 0);
		return;
	}

	std::map<std::string, Client *> clientsList = tmp->getClients();
	std::map<std::string, Client *>::iterator it2 = clientsList.begin();
	for (; it2 != clientsList.end(); ++it2) {
		if (it2->first == msg->params[1])
			break;
	}
	if (it2 == clientsList.end()) {
		std::string errNotOnChannel = ERR_NOTONCHANNEL(client->getNick(), nameChannel);
		send(client->getFd(), errNotOnChannel.c_str(), errNotOnChannel.size(), 0);
		return;
	}

	std::string rpl = it2->first + " was kicked from " + nameChannel + " by " + client->getNick();
	if (msg->params.size() == 2)
		rpl += " [" + client->getNick() + "]\n";
	else {
		std::string params = "[";
		std::vector<std::string>::iterator it = msg->params.begin() + 2;
		for (; it != msg->params.end(); it++) {
			params += *it;
			if (it + 1 != msg->params.end())
				params += " ";
		}
		params += "]";
		rpl += " " + params + "\n";
	}
	it->first->sendMessageToAllClients(rpl);

	// erase the client from the channel
	tmp->removeClient(it2->second);

	// erase the channel from the client
	it2->second->removeChannel(tmp);

	// erase the client from the channel's clients list
	clientsList.erase(it2);
	
	// if the channel is empty, delete it
	if (tmp->getClients().size() == 0)
		server->removeChannel(tmp->getName());

}

// KICK <channel> <user> [<comment>]

// parametres: channel, client, op: comment pour expliquer la raison de le kick
