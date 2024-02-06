/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorin <kmorin@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:36:11 by kmorin            #+#    #+#             */
/*   Updated: 2024/02/06 10:39:22 by kmorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Commands/Topic.hpp"

Topic::Topic(void) {}

Topic::~Topic(void) {}

/**
 * https://datatracker.ietf.org/doc/html/rfc2812#section-3.2.4
 *
 * Parameter:
 * 		<channel> [<topic>]
 *
 * If the number of parameters is not valid, ERR_NEEDMOREPARAMS
 * If one parameter is passed,
 * 		send to the client RPL_TOPIC if the topic is not empty or
 * 		RPL_NOTOPIC if the topic is empty
 * If the client is not on the channel, ERR_NOTONCHANNEL
 * If the client is not a operator on this channel and the channel is in +t mode, ERR_CHANOPRIVSNEEDED
 * Else sets the topic to what is passed after the channel parameter and send RPL_TOPIC to the channel
 *
 * @param server The server object.
 * @param msg The message object containing the command and parameters.
 * @param client The client object.
*/
void	Topic::execute(Server* server, t_Message* msg, Client* client) {

	std::string	response;

	// Check if there is enough parameters
	if (msg->params.size() < 1) {
		response = ERR_NEEDMOREPARAMS(client->getAddress(), client->getNick(), msg->command);
		client->sendMessage(response);
		return;
	}

	std::string	channelName = msg->params[0];

	Channel*	channel = server->getChannel(channelName);

	// If there is no second parameter we send the topic of the channel asked
	if (msg->params[1].empty()) {
		response = channel->getTopic();
		if (response.empty())
			response = RPL_NOTOPIC(client->getAddress(), client->getNick(), channelName);
		else
			response = RPL_TOPIC(client->getAddress(), client->getNick(), channelName, response);

		client->sendMessage(response);
		return;
	}

	// Check if the client is on the channel
	std::map<Channel*, bool>::iterator	it = client->getChannel(channelName);
	if (it == client->getChannels().end()) {
		response = ERR_NOTONCHANNEL(client->getAddress(), client->getNick(), channelName);
		client->sendMessage(response);
		return;
	}

	// Check for who the command is available
	// If the command is reserved for chanop, check that the client is one
	if (channel->getT() == true && it->second == false) {
		response = ERR_CHANOPRIVSNEEDED(client->getAddress(), client->getNick(), channelName);
		client->sendMessage(response);
		return;
	}

	std::string	params = getParams(msg, 1);
	if (params.empty() == false && params[0] == ':') {
		if (params.size() > 2 && params[1] == ' ')
			params.erase(0, 2);
		else
			params.erase(0, 1);
	}

	channel->setTopic(params);

	response = RPL_TOPIC(client->getAddress(), client->getNick(), channelName, params);
	channel->sendMessageToAllClients(response);
}
