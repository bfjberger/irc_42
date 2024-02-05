/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorin <kmorin@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:36:11 by kmorin            #+#    #+#             */
/*   Updated: 2024/02/05 13:01:04 by kmorin           ###   ########.fr       */
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
 * If the number of parameters is not valid, ERR message
 * If one parameter is passed,
 * 	send the RPL to the client depending on if the topic is empty or not
 * If the client is not on the channel, ERR message
 * If the client is not a operator on this channel, ERR message
 * Else sets the topic to what is passed after the channel parameter
 *
 * @param server The server object.
 * @param msg The message object containing the command and parameters.
 * @param client The client object.
*/
void	Topic::execute(Server* server, t_Message* msg, Client* client) {

	std::string	response;

	// Check if there is enough parameters
	if (msg->params.size() < 1) {
		response = ERR_NEEDMOREPARAMS(client->getNick(), msg->command);
		client->sendMessage(response);
		return;
	}

	std::string	channelName = msg->params[0];

	Channel*	channel = server->getChannel(channelName);

	// If there is no second parameter we send the topic of the channel asked
	if (msg->params[1].empty()) {
		response = channel->getTopic();
		if (response.empty())
			response = RPL_NOTOPIC(client->getNick(), channelName);
		else
			response = RPL_TOPIC(client->getNick(), channelName, response);

		client->sendMessage(response);
		return;
	}

	// Check if the client is on the channel
	std::map<Channel*, bool>::iterator	it = client->getChannel(channelName);
	if (it == client->getChannels().end()) {
		response = ERR_NOTONCHANNEL(client->getNick(), channelName);
		client->sendMessage(response);
		return;
	}

	// Check if the client is a channel operator on this channel
	if (it->second == false) {
		response = ERR_CHANOPRIVSNEEDED(client->getNick(), channelName);
		client->sendMessage(response);
		return;
	}

	std::string	params = getParams(msg, 1);

	channel->setTopic(params);

	response = "The topic of the channel " + channel->getName() + " is now " + params + "\r\n";
	client->sendMessage(response);
}
