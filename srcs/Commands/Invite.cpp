/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorin <kmorin@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:35:58 by kmorin            #+#    #+#             */
/*   Updated: 2024/01/31 14:18:05 by kmorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Commands/Invite.hpp"

Invite::Invite(void) {}

Invite::~Invite(void) {}

/**
 * 
*/

void	Invite::execute(Server* server, t_Message* msg, Client* client) {

	// Check if there is enough parameters
	if (msg->params.size() < 2)
	{
		std::string	tmp = ERR_NEEDMOREPARAMS(client->getNick(), msg->command);
		send(client->getFd(), tmp.c_str(), tmp.size(), 0);
		return;
	}

	// Check if the client to be invited exist
	if (!server->getClient(msg->params[0]))
	{
		std::string	tmp = ERR_NOSUCHNICK(client->getNick(), msg->params[0]);
		send(client->getFd(), tmp.c_str(), tmp.size(), 0);
		return;
	}

	std::string	nameChannel = msg->params[1];
	Channel		*channel = server->getChannel(nameChannel);

	// Check if the client to be invited is not already on the channel
	Client*	invitedClientOnChan = channel->getClient(msg->params[0]);
	if (invitedClientOnChan)
	{
		std::string errOnChannel = ERR_USERONCHANNEL(client->getNick(), msg->params[0], nameChannel);
		send(client->getFd(), errOnChannel.c_str(), errOnChannel.size(), 0);
		return;
	}

	// Check if the client sending the invitation is on the channel
	std::map<Channel*, bool>::iterator	clientSendingIt = client->getChannel(nameChannel);
	if (clientSendingIt == client->getChannels().end()) {
		std::string errNotOnChannel = ERR_NOTONCHANNEL(client->getNick(), nameChannel);
		send(client->getFd(), errNotOnChannel.c_str(), errNotOnChannel.size(), 0);
		return;
	}

	// Check if the client sending the invitation is a channel operator on this channel
	if (clientSendingIt->second == false) {
		std::string errNotOperator = ERR_CHANOPRIVSNEEDED(client->getNick(), nameChannel);
		send(client->getFd(), errNotOperator.c_str(), errNotOperator.size(), 0);
		return;
	}

	Client*	invitedClient = server->getClient(msg->params[0]);

	std::string rpl_invit = RPL_INVITING(invitedClient->getNick(), nameChannel, client->getNick());
	send(invitedClient->getFd(), rpl_invit.c_str(), rpl_invit.size(), 0);

	rpl_invit = "An invitation has been sent to " + invitedClient->getNick() + "\r\n";
	send(client->getFd(), rpl_invit.c_str(), rpl_invit.size(), 0);

	channel->setInvitedClientVector(invitedClient->getNick());
}
