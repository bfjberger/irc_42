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

/**
 * Executes the PRIVMSG command.
 * Sends a message to either a channel or a client.
 * 
 * @param server The server instance.
 * @param msg The message containing the command and parameters.
 * @param client The client who sent the command.
 */
void	Privmsg::execute(Server* server, t_Message* msg, Client* client) {

	// rplMsg is the message to send to the channel or the client
	std::string rplMsg = getParams(msg, 1) + "\r\n";
	if (rplMsg[0] == ':') {
		rplMsg.erase(0, 1);
	}

	// msg->params[0] is the channel or the client to send the message to
	// params[1+] is the message to send
	if (msg->params.size() < 2) {
		std::string errNeedMore = ERR_NEEDMOREPARAMS(client->getNick(), msg->command);
		client->sendMessage(errNeedMore);
		return;
	}

	// if the first param is a channel
	// send the message to all the clients in the channel
	if (server->isChannel(msg->params[0]) == true) {
		Channel* channel = server->getChannel(msg->params[0]);
		if (channel != NULL) {
			std::string clientNick = client->getNick();
			std::string tmp = ":" + clientNick + "!" + client->getUserName() + "@" + client->getHostname() + " PRIVMSG " + msg->params[0];
			tmp += " " + rplMsg + "\r\n";
			channel->sendToAllButOne(tmp, client);
		}
		else {
			std::string errNoChannel = ERR_NOSUCHCHANNEL(client->getNick(), msg->params[0]);
			client->sendMessage(errNoChannel);
		}
	}

	// if the first param is a client
	// send the message to the client
	else if (server->isNick(msg->params[0]) == true) {
		Client* target = server->getClient(msg->params[0]);
		if (target != NULL) {
			std::string rplPrivmsg = RPL_PRIVMSG(client->getNick(), rplMsg);
			std::cout << COLOR("[" << client->getNick() << "] -> [" << target->getNick() << "] : " << rplMsg, GREEN) << std::endl;
			target->sendMessage(rplPrivmsg);
		}
		else {
			std::string errNoNick = ERR_NOSUCHNICK(client->getNick(), msg->params[0]);
			client->sendMessage(errNoNick);
		}
	}
	else {
		std::string errNoNick = ERR_NOSUCHNICK(client->getNick(), msg->params[0]);
		client->sendMessage(errNoNick);
	}
}
