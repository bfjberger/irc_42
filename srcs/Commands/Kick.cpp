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
		client->sendMessage(errNeedMore);
		return;
	}

	std::string nameChannel = msg->params[0];

	Channel *channel = server->getChannel(nameChannel);

	if (!channel) {
		std::string errNoSuchChannel = ERR_NOSUCHCHANNEL(client->getNick(), nameChannel);
		client->sendMessage(errNoSuchChannel);
		return;
	}
	std::map<Channel *, bool> other = client->getChannels();
	std::map<Channel *, bool>::iterator it = other.find(channel);
	if (it == other.end()) {
		std::cout << COLOR("red", "ERROR: ") << "Client " << client->getNick() << " is not in channel " << nameChannel << std::endl;
		return;
	}
	if (it->second == false) {
		std::string errNotOperator = ERR_CHANOPRIVSNEEDED(client->getNick(), nameChannel);
		client->sendMessage(errNotOperator);
		return;
	}

	std::map<std::string, Client *> clientsList = channel->getClients();
	std::map<std::string, Client *>::iterator it2 = clientsList.begin();
	for (; it2 != clientsList.end(); ++it2) {
		if (it2->first == msg->params[1])
			break;
	}
	if (it2 == clientsList.end()) {
		std::string errNotOnChannel = ERR_NOTONCHANNEL(client->getNick(), nameChannel);
		client->sendMessage(errNotOnChannel);
		return;
	}

	// std::string rpl = it2->first + " was kicked from " + nameChannel + " by " + client->getNick();
	std::string rpl = ":" + USER_ID(client) + " KICK " + nameChannel + " " + it2->first;
	std::cout << "msg->params.size() = " << msg->params.size() << std::endl;
	if (msg->params.size() == 3 && msg->params[2].length() == 1) {
		msg->params[2] = "by Channel Operator\r\n";
	}
	std::cout << "msg->params.size() = " << msg->params.size() << std::endl;
	if (msg->params.size() == 2) {
		rpl += " by Channel Operator\r\n";
	}
	else
		rpl += " " + getParams(msg, 2) + "\r\n";
	it->first->sendMessageToAllClients(rpl);

	// erase the client from the channel
	channel->removeClient(it2->second);

	// erase the channel from the client
	it2->second->removeChannel(channel);

	// erase the client from the channel's clients list
	clientsList.erase(it2);
	
	// if the channel is empty, delete it
	if (channel->getClients().size() == 0)
		server->removeChannel(channel->getName());

}

// KICK <channel> <user> [<comment>]

// parametres: channel, client, op: comment pour expliquer la raison de le kick
