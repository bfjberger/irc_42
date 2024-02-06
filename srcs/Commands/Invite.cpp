/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorin <kmorin@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:35:58 by kmorin            #+#    #+#             */
/*   Updated: 2024/02/06 10:27:19 by kmorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Commands/Invite.hpp"

Invite::Invite(void) {}

Invite::~Invite(void) {}

/**
 * https://datatracker.ietf.org/doc/html/rfc2812#section-3.2.7
 *
 * Parameters:
 * 		<nickname> <channel>
 *
 * If the number of parameters is not valid, ERR_NEEDMOREPARAMS
 * If the client to be invited does not exist, ERR_NOSUCHNICK
 * If the client to be invited is already on the channel, ERR_USERONCHANNEL
 * If the client inviting is not on the channel, ERR_NOTONCHANNEL
 * If the client inviting it not a chanop, ERR_CHANOPRIVSNEEDED
 * Else, send RPL_INVITING to the client invited, send a custom confirmation of invitation to the client inviting
 *
 * @param server The server Object.
 * @param msg The message object containing the command and parameters.
 * @param client The client object.
*/
void	Invite::execute(Server* server, t_Message* msg, Client* client) {

	// Check if there is enough parameters
	if (msg->params.size() < 2)
	{
		std::string	errNeedMoreParams = ERR_NEEDMOREPARAMS(client->getAddress(), client->getNick(), msg->command);
		client->sendMessage(errNeedMoreParams);
		return;
	}

	// Check if the client to be invited exist
	if (!server->getClient(msg->params[0]))
	{
		std::string	errNoSuchNick = ERR_NOSUCHNICK(client->getAddress(), client->getNick(), msg->params[0]);
		client->sendMessage(errNoSuchNick);
		return;
	}

	std::string	nameChannel = msg->params[1];
	Channel		*channel = server->getChannel(nameChannel);

	// Check if the client to be invited is not already on the channel
	Client*	invitedClientOnChan = channel->getClient(msg->params[0]);
	if (invitedClientOnChan)
	{
		std::string errOnChannel = ERR_USERONCHANNEL(client->getAddress(), client->getNick(), msg->params[0], nameChannel);
		client->sendMessage(errOnChannel);
		return;
	}

	// Check if the client sending the invitation is on the channel
	std::map<Channel*, bool>::iterator	clientSendingIt = client->getChannel(nameChannel);
	if (clientSendingIt == client->getChannels().end()) {
		std::string errNotOnChannel = ERR_NOTONCHANNEL(client->getAddress(), client->getNick(), nameChannel);
		client->sendMessage(errNotOnChannel);
		return;
	}

	// Check if the client sending the invitation is a channel operator on this channel
	if (clientSendingIt->second == false) {
		std::string errNotOperator = ERR_CHANOPRIVSNEEDED(client->getAddress(), client->getNick(), nameChannel);
		client->sendMessage(errNotOperator);
		return;
	}

	Client*	invitedClient = server->getClient(msg->params[0]);

	std::string rpl_invit = RPL_INVITING(client->getAddress(), invitedClient->getNick(), nameChannel, client->getNick());
	invitedClient->sendMessage(rpl_invit);

	rpl_invit = "An invitation has been sent to " + invitedClient->getNick() + "\r\n";
	client->sendMessage(rpl_invit);

	channel->setInvitedClientVector(invitedClient->getNick());
}
