/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorin <kmorin@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:36:09 by kmorin            #+#    #+#             */
/*   Updated: 2024/01/24 14:05:30 by kmorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Commands/Privmsg.hpp"

Privmsg::Privmsg(void) {}

Privmsg::~Privmsg(void) {}

void	Privmsg::execute(Server* server, t_Message* msg, Client* client) {

	(void) server;
	(void) msg;
	(void) client;

	std::string rplMsg = getParams(msg, 1) + "\r\n";
	if (rplMsg[0] == ':') {
		rplMsg.erase(0, 1);
	}

	if (msg->params.size() < 2) {
		std::string errNeedMore = ERR_NEEDMOREPARAMS(client->getNick(), msg->command);
		send(client->getFd(), errNeedMore.c_str(), errNeedMore.size(), 0);
		return;
	}

	if (server->isChannel(msg->params[0]) == true) {
		Channel* channel = server->getChannel(msg->params[0]);
		if (channel != NULL) {
			std::string clientNick = client->getNick();
			// if the client is the operator of the channel add the operator symbol to the client string
			// if (channel->isOperator(clientNick) == true) {
			// 	clientNick = "@" + clientNick;
			// }
			std::string tmp = ":" + clientNick + "!" + client->getUserName() + "@" + client->getHostname() + " PRIVMSG " + msg->params[0];
			tmp += " " + rplMsg + "\r\n";
			channel->sendToAllButOne(tmp, client);
		}
		else {
			std::string errNoChannel = ERR_NOSUCHCHANNEL(client->getNick(), msg->params[0]);
			send(client->getFd(), errNoChannel.c_str(), errNoChannel.size(), 0);
		}
	}
	else if (server->isNick(msg->params[0]) == true) {
		Client* target = server->getClient(msg->params[0]);
		if (target != NULL) {
			std::string rplPrivmsg = RPL_PRIVMSG(client->getNick(), rplMsg);
			std::cout << COLOR("[" << client->getNick() << "] -> [" << target->getNick() << "] : " << rplMsg, GREEN) << std::endl;
			send(target->getFd(), rplPrivmsg.c_str(), rplPrivmsg.size(), 0);
		}
		else {
			std::string errNoNick = ERR_NOSUCHNICK(client->getNick(), msg->params[0]);
			send(client->getFd(), errNoNick.c_str(), errNoNick.size(), 0);
		}
	}
	else {
		std::string errNoNick = ERR_NOSUCHNICK(client->getNick(), msg->params[0]);
		send(client->getFd(), errNoNick.c_str(), errNoNick.size(), 0);
	}
}
