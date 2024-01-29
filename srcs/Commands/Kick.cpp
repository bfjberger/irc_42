/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bberger <bberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:36:00 by kmorin            #+#    #+#             */
/*   Updated: 2024/01/29 17:17:30 by bberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Commands/Kick.hpp"

Kick::Kick(void) {}

Kick::~Kick(void) {}

void	Kick::execute(Server* server, t_Message* msg, Client* client) {
    
	
	if (msg->params.size() < 2)
	{
		std::string	tmp5 = ERR_NEEDMOREPARAMS(client->getNick(), msg->command);
		send(client->getFd(), tmp5.c_str(), tmp5.size(), 0);
		return;
	}
	
	std::string    nameChannel = msg->params[0];

	Channel*    tmp = server->getChannel(nameChannel);

    if (!tmp) 
	{
		std::string	tmp2 = ERR_NOSUCHCHANNEL(client->getNick(), nameChannel);
		send(client->getFd(), tmp2.c_str(), tmp2.size(), 0);
		return;
    }

    std::map<Channel*, bool>    other = client->getChannels();
    std::map<Channel*, bool>::iterator it = other.find(tmp);
	if (it == other.end())
		std::cout << "Enter in here" << std::endl;
    if (it->second == false) 
	{
		std::string tmp3 = ERR_CHANOPRIVSNEEDED(client->getNick(), nameChannel);
		send(client->getFd(), tmp3.c_str(), tmp3.size(), 0);
		return;
    }
	
	std::map<std::string, Client*>    clientsList = tmp->getClients();
	std::map<std::string, Client*>::iterator it2 = clientsList.begin();
    for (; it2 != clientsList.end(); ++it2) {
        if (it2->first == msg->params[1])
            break;
    }
	if (it2 == clientsList.end())
	{
	std::string tmp4 = ERR_NOTONCHANNEL(client->getNick(), nameChannel);
		send(client->getFd(), tmp4.c_str(), tmp4.size(), 0);
		return;
	}
	
	clientsList.erase(it2);
	std::string rpl = it2->first + " was kicked from " + nameChannel + " by " + client->getNick();
	if (msg->params[2].empty() == false)
	{
		rpl += " " + msg->params[2] + "\n";
	}
	else 
		rpl += " " + client->getNick() + "\n";
	it->first->sendMessageToAllClients(rpl);
	
	// user was kicked from #testk by chanopuser [chanopuser]
	
	
	std::map<Channel *, bool> toBeKickedChannel = it2->second->getChannels();
	toBeKickedChannel.erase(server->getChannel(nameChannel));
	// user was kicked from #testk by chanopuser [byebye]
	
	
	
	std::cout << "kick" << std::endl;
}

// KICK <channel> <user> [<comment>]

// parametres: channel, client, op: comment pour expliquer la raison de le kick





