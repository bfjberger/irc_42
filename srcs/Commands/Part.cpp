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
		std::string	tmp = ERR_NEEDMOREPARAMS(client->getNick(), msg->command);
		send(client->getFd(), tmp.c_str(), tmp.size(), 0);
		return;
	}

	std::string    nameChannel = msg->params[0];
	Channel*    channel = server->getChannel(nameChannel);

    if (!channel)
	{
		std::string	tmp2 = ERR_NOSUCHCHANNEL(client->getNick(), nameChannel);
		send(client->getFd(), tmp2.c_str(), tmp2.size(), 0);
		return;
    }


	std::map<std::string, Client*>    clientsList = channel->getClients();
	// std::map<std::string, Client*>::iterator it2 = clientsList.begin();
    // for (; it2 != clientsList.end(); ++it2)
	// {
    //     if (it2->first == msg->params[1])
    //         break;
    // }

	if (clientsList.find(client->getNick()) == clientsList.end())
	{
	std::string tmp4 = ERR_NOTONCHANNEL(client->getNick(), nameChannel);
		send(client->getFd(), tmp4.c_str(), tmp4.size(), 0);
		return;
	}
	std::map<Channel*, bool>    other = client->getChannels();
	std::map<Channel*, bool>::iterator it = other.find(channel);

	std::string rpl = client->getNick() + " parts from " + nameChannel;
	if (msg->params.size() == 1)
		rpl += " " + client->getNick() + "\r\n";
	else {
		std::string	params;
		std::vector<std::string>::iterator	it = msg->params.begin() + 1;
		for (; it != msg->params.end(); it++) {
			params += *it;
			if (it + 1 != msg->params.end())
				params += " ";
		}
		rpl += " " + params + "\r\n";
	}
	it->first->sendMessageToAllClients(rpl);

	channel->removeClient(client);

	client->removeChannel(channel);

	if (channel->getClients().size() == 0)
		server->removeChannel(channel->getName());
}


// <channel> *( "," <channel> ) [ <Part Message> ]
