/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorin <kmorin@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:35:59 by kmorin            #+#    #+#             */
/*   Updated: 2024/02/05 13:27:39 by kmorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Commands/Join.hpp"

Join::Join(void) {}

Join::~Join(void) {}

/**
 * https://datatracker.ietf.org/doc/html/rfc2812#section-3.2.1
 *
 * Parameters:
 * 		<channel> [<key>]
 *
 * At the creation of a channel, every other arguments, outside the channel name, are ignored
 *
 * If the client is already in too many channel, ERR message
 * If the number of parameters is not valid, ERR message
 * If the channel name is not valid, ERR message
 * If the channel does not exist yet, it is created in channelCreation()
 * If the channel has a password, it is handled in joinChannelPassword()
 * If the channel has a user limit,
 * 		if the limit is reached, ERR message
 * 		if the limit is not reached, the joining is handled in joinChannel()
 *
 * @param server The server Object.
 * @param msg The message object containing the command and parameters.
 * @param client The client object.
*/

void	Join::channelCreation(Server* server, t_Message* msg, Client* client, Channel* channel) {

	channel = new Channel(msg->params[0]);
	server->addChannel(channel);

	client->setCurrentChannel(channel->getName());
	client->setInChannel(true);

	//add the channel to which the client is part of and indicate he is an operator on this one
	client->addChannel(channel, true);

	channel->addClient(client);

	// std::string	response = ":localhost " + client->getNick() + " " + channel->getName() + " :You have joined the newly created channel " + msg->params[0] + "\r\n"; // TODO: Change this message to be IRSSI compliant
	// send(client->getFd(), response.c_str(), response.length(), 0);
	std::string response2 = RPL_JOIN(client, msg->params[0]);
	client->sendMessage(response2);

}

void	Join::joinChannelPassword(Server* server, t_Message* msg, Client* client, Channel* channel) {

	if (msg->params.size() < 2) {
		std::string	response = ERR_NEEDMOREPARAMS(client->getNick(), msg->command);
		client->sendMessage(response);
		return;
	}

	if (msg->params[1] != channel->getPassword()) {
		std::string	response = ERR_BADCHANNELKEY(client->getNick(), channel->getName());
		client->sendMessage(response);
	}
	else
		joinChannel(server, msg, client, channel);
}

void	Join::joinChannel(Server* server, t_Message* msg, Client* client, Channel* channel) {

	(void) server;

	// Set the client's current channel
	client->setCurrentChannel(channel->getName());
	client->setInChannel(true);

	//add the channel to which the client is part of and indicate he is not an operator
	client->addChannel(channel, false);

	// Add the client to the channel
	channel->addClient(client);

	// Send a response to the client
	// std::string response = "You have joined channel " + msg->params[0] + "\r\n"; // TODO: Change this message to be IRSSI compliant
	// response = ":" + client->getNick() + " " + channel->getName() + " :You have joined channel " + msg->params[0] + "\r\n";
	// send(client->getFd(), response.c_str(), response.length(), 0);
	std::string response2 = RPL_JOIN(client, msg->params[0]);
	client->sendMessage(response2);
	// send(client->getFd(), response2.c_str(), response2.length(), 0);

	// std::string	toChan = "The user " + client->getNick() + " has joined this channel.\r\n"; // TODO : Change this message to be IRSSI compliant
	// channel->sendToAllButOne(toChan, client);
	channel->sendToAllButOne(response2, client);

}

void Join::execute(Server* server, t_Message* msg, Client* client) {

	// Check if the client is not in too many channel
	if (static_cast<int>(client->getChannels().size()) == client->getMaxChannels()) {
		std::string	response = ERR_TOOMANYCHANNELS(client->getNick(), msg->params[0]);
		client->sendMessage(response);
		return;
	}

	// Check if there is enough parameters
	if (msg->params.size() < 1) {
		std::string	response = ERR_NEEDMOREPARAMS(client->getNick(), msg->command);
		client->sendMessage(response);
		return;
	}

	std::string channelName = msg->params[0];

	// Check for forbidden caracters
	if (channelName.find(' ') != channelName.npos || channelName.find(',') != channelName.npos || \
		channelName.find(7) != channelName.npos || channelName.size() > 50) {
		std::string	response = ERR_NOSUCHCHANNEL(client->getNick(), channelName);
		client->sendMessage(response);
		return;
	}

	if (channelName[0] != '#') {
		std::string	response = "A '#' is needed at the beginning of the channel name.\r\n";
		client->sendMessage(response);
		return;
	}

	// Check if the channel already exists
	Channel* channel = server->getChannel(channelName);
	if (channel == NULL) {
		channelCreation(server, msg, client, channel);
		return;
	}

	// Check if the channel has a password
	if (channel->getK() == true) {
		joinChannelPassword(server, msg, client, channel);
		return;
	}

	// Check if the channel has a user limit
	if (channel->getL() == true) {
		if (channel->getUserLimit() == static_cast<int>(channel->getClients().size())) {
			std::string	response = ERR_CHANNELISFULL(client->getNick(), channel->getName());
			client->sendMessage(response);
		}
		else
			joinChannel(server, msg, client, channel);
		return;
	}

	// Check if the channel is in invite-only
	if (channel->getI() == true) {
		if (channel->getInvitedClientVector(client->getNick()))
			joinChannel(server, msg, client, channel);
		else {
			std::string	response = ERR_INVITEONLYCHAN(client->getNick(), channel->getName());
			client->sendMessage(response);
		}
		return;
	}

	joinChannel(server, msg, client, channel);
}
