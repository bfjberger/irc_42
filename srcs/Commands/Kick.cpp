/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorin <kmorin@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:36:00 by kmorin            #+#    #+#             */
/*   Updated: 2024/02/06 10:19:35 by kmorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Commands/Kick.hpp"

Kick::Kick(void) {}

Kick::~Kick(void) {}

/**
 * https://datatracker.ietf.org/doc/html/rfc2812#section-3.2.7
 *
 * Parameters:
 * 		<nickname> <channel> [<comment>]
 *
 * Kick a user from a specific channel
 *
 * If the number of parameters is not valid, ERR message
 * If the channel does not exist, ERR message
 * If the user attempting to kick is not on the channel, ERR message
 * If the user attempting to kick is not chanop, ERR message
 * If the user targeted to be kick is not on the channel, ERR message
 *
 * @param server The server Object.
 * @param msg The message object containing the command and parameters.
 * @param client The client object.
*/
void Kick::execute(Server *server, t_Message *msg, Client *client) {

	// Check if there is enough parameters
	if (msg->params.size() < 2) {
		std::string errNeedMore = ERR_NEEDMOREPARAMS(client->getAddress(), client->getNick(), msg->command);
		client->sendMessage(errNeedMore);
		return;
	}

	std::string channelName = msg->params[0];

	Channel *channel = server->getChannel(channelName);

	// Check if the channel exists
	if (!channel) {
		std::string errNoSuchChannel = ERR_NOSUCHCHANNEL(client->getAddress(), client->getNick(), channelName);
		client->sendMessage(errNoSuchChannel);
		return;
	}

	std::map<Channel*, bool>::iterator	it = client->getChannel(channelName);
	// Check if the client attempting to kick is on the channel
	if (it == client->getChannels().end()) {
		std::string	errNotOnChannel = ERR_NOTONCHANNEL(client->getAddress(), client->getNick(), channelName);
		client->sendMessage(errNotOnChannel);
		return;
	}
	// Check if the client attempting to kick is chanop
	if (it->second == false) {
		std::string errNotOperator = ERR_CHANOPRIVSNEEDED(client->getAddress(), client->getNick(), channelName);
		client->sendMessage(errNotOperator);
		return;
	}

	// std::map<std::string, Client *> clientsList = channel->getClients();
	// std::map<std::string, Client *>::iterator it2 = clientsList.begin();
	// for (; it2 != clientsList.end(); ++it2) {
	// 	if (it2->first == msg->params[1])
	// 		break;
	// }
	// if (it2 == clientsList.end()) {
	// 	std::string errNotOnChannel = ERR_NOTONCHANNEL(client->getAddress(), client->getNick(), channelName);
	// 	client->sendMessage(errNotOnChannel);
	// 	return;
	// }

	Client*	target = channel->getClient(msg->params[1]);
	// Check if the target is on the channel
	if (!target) {
		std::string errNotOnChannel = ERR_USERNOTINCHANNEL(client->getAddress(), client->getNick(), msg->params[1], channelName);
		client->sendMessage(errNotOnChannel);
		return;
	}

	std::string response = ":" + USER_ID(client) + " KICK " + channelName + " " + target->getNick() + " ";
	std::string	comment;

	if (msg->params.size() > 2 && msg->params[2].length() > 1)
		comment = getParams(msg, 2);
	else
		comment = client->getNick();
	comment += "\r\n";
	response += comment;

	channel->sendMessageToAllClients(response);

	// erase the client from the channel
	channel->removeClient(target);

	// erase the channel from the client
	target->removeChannel(channel);

	// if the channel is empty, delete it
	if (channel->getClients().size() == 0)
		server->removeChannel(channel->getName());
}
