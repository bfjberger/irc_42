/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorin <kmorin@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:36:06 by kmorin            #+#    #+#             */
/*   Updated: 2024/01/31 11:36:38 by kmorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Commands/Part.hpp"

Part::Part(void) {}

Part::~Part(void) {}

void	Part::execute(Server* server, t_Message* msg, Client* client)
{

	if (msg->params.size() < 1)
	{
		std::string	errNeedMoreParams = ERR_NEEDMOREPARAMS(client->getNick(), msg->command);
		client->sendMessage(errNeedMoreParams);
		return;
	}

	std::string    nameChannel = msg->params[0];
	Channel*    channel = server->getChannel(nameChannel);

    if (!channel)
	{
		std::string	errNoSuchChannel = ERR_NOSUCHCHANNEL(client->getNick(), nameChannel);
		client->sendMessage(errNoSuchChannel);
		return;
    }


	std::map<std::string, Client*>    clientsList = channel->getClients();

	if (clientsList.find(client->getNick()) == clientsList.end())
	{
		std::string errNotOnChannel = ERR_NOTONCHANNEL(client->getNick(), nameChannel);
		client->sendMessage(errNotOnChannel);
		return;
	}
	std::map<Channel*, bool>    other = client->getChannels();
	std::map<Channel*, bool>::iterator it = other.find(channel);

	// std::string rpl = client->getNick() + " parts from " + nameChannel;
	std::string rpl = ":" + USER_ID(client) + " PART " + nameChannel;
	if (msg->params.size() == 1) {
		rpl += " .\r\n";
		// rpl += " " + client->getNick() + "\r\n";
	}
	else
		rpl += " [" + getParams(msg, 1) + "]\r\n";
	it->first->sendMessageToAllClients(rpl);
	
	client->removeChannel(channel);
	channel->removeClient(client);

	if (channel->getClients().size() == 0)
		server->removeChannel(channel->getName());
}


// <channel> *( "," <channel> ) [ <Part Message> ]
