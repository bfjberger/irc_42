/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorin <kmorin@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:36:06 by kmorin            #+#    #+#             */
/*   Updated: 2024/02/06 10:35:21 by kmorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Commands/Part.hpp"

Part::Part(void) {}

Part::~Part(void) {}

/**
 * https://datatracker.ietf.org/doc/html/rfc2812#section-3.2.2
 *
 * Parameters:
 * 		<channel> [ <Part Message> ]
 *
 * If the number of parameters is not valid, ERR_NEEDMOREPARAMS
 * If the channel to part from does not exist, ERR_NOSUCHCHANNEL
 * If the client is not part of the channel to part from, ERR_NOTONCHANNEL
 * Else, a custom message is sent to the channel indicating that the client left the channel with the comment if present
 * 		the server, handle the cleaning in the maps
 *
 * If the channel has no member left, we delete it from the server
 *
 * @param server The server Object.
 * @param msg The message object containing the command and parameters.
 * @param client The client object.
*/
void	Part::execute(Server* server, t_Message* msg, Client* client)
{

	std::string	response;

	// Check if there is enough parameters
	if (msg->params.size() < 1)
	{
		response = ERR_NEEDMOREPARAMS(client->getAddress(), client->getNick(), msg->command);
		client->sendMessage(response);
		return;
	}

	std::string	nameChannel = msg->params[0];
	Channel*	channel = server->getChannel(nameChannel);

	// Check if the channel asked exist
	if (!channel)
	{
		response = ERR_NOSUCHCHANNEL(client->getAddress(), client->getNick(), nameChannel);
		client->sendMessage(response);
		return;
	}

	// Check if the client is a member of the channel
	Client*	clientParting = channel->getClient(client->getNick());
	if (!clientParting)
	{
		response = ERR_NOTONCHANNEL(client->getAddress(), client->getNick(), nameChannel);
		client->sendMessage(response);
		return;
	}

	// Prepare the message to send to all clients to announce the depart of the client
	response = ":" + USER_ID(client) + " PART " + nameChannel;
	if (msg->params.size() == 1)
		response += " \r\n";
	else
		response += " " + getParams(msg, 1) + "\r\n";
	channel->sendMessageToAllClients(response);

	// Remove the channel from the map of the channels where the client is
	// Remove the client from the map of clients which are member of the channel
	client->removeChannel(channel);
	channel->removeClient(client);

	// If the channel has no member left, remove it
	if (channel->getClients().size() == 0)
		server->removeChannel(channel->getName());
}
