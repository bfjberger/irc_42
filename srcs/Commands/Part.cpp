/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberger <bberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:36:06 by kmorin            #+#    #+#             */
/*   Updated: 2024/01/30 11:51:41 by bberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Commands/Part.hpp"

Part::Part(void) {}

Part::~Part(void) {}

void	Part::execute(Server* server, t_Message* msg, Client* client) 
{
	std::cout << "part" << std::endl;

	if (msg->params.size() < 2) 
	{
		std::string	tmp = ERR_NEEDMOREPARAMS(client->getNick(), msg->command);
		send(client->getFd(), tmp.c_str(), tmp.size(), 0);
		return;
	}
		
	std::string    nameChannel = msg->params[0];
	Channel*    tmp6 = server->getChannel(nameChannel);

    if (!tmp6)
	{
		std::string	tmp2 = ERR_NOSUCHCHANNEL(client->getNick(), nameChannel);
		send(client->getFd(), tmp2.c_str(), tmp2.size(), 0);
		return;
    }


	std::map<std::string, Client*>    clientsList = tmp6->getClients();
	std::map<std::string, Client*>::iterator it2 = clientsList.begin();
    for (; it2 != clientsList.end(); ++it2) 
	{
        if (it2->first == msg->params[1])
            break;
    }
	if (it2 == clientsList.end())
	{
	std::string tmp4 = ERR_NOTONCHANNEL(client->getNick(), nameChannel);
		send(client->getFd(), tmp4.c_str(), tmp4.size(), 0);
		return;
	}
	std::map<Channel*, bool>    other = client->getChannels();
	std::map<Channel*, bool>::iterator it = other.find(tmp6);

	std::string rpl = it2->first + " was parted from " + nameChannel + " by " + client->getNick();
	if (msg->params.size() == 2)
		rpl += " " + client->getNick() + "\n";
	else {
		std::string	params;
		std::vector<std::string>::iterator	it = msg->params.begin() + 2;
		for (; it != msg->params.end(); it++) {
			params += *it;
			if (it + 1 != msg->params.end())
				params += " ";
		}
		rpl += " " + params + "\n";
	}
	it->first->sendMessageToAllClients(rpl);

	std::map<Channel *, bool> toBeKickedChannel = it2->second->getChannels();
	toBeKickedChannel.erase(server->getChannel(nameChannel));
	clientsList.erase(it2);


}


// <channel> *( "," <channel> ) [ <Part Message> ]
