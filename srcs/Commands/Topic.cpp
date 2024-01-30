/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorin <kmorin@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:36:11 by kmorin            #+#    #+#             */
/*   Updated: 2024/01/24 14:05:41 by kmorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Commands/Topic.hpp"

Topic::Topic(void) {}

Topic::~Topic(void) {}

void	Topic::execute(Server* server, t_Message* msg, Client* client) {

	std::cout << "topic" << std::endl;

	std::string	nameChannel = msg->params[0];

	Channel*	tmp = server->getChannel(nameChannel);

	std::map<Channel*, bool>    other = client->getChannels();
	std::map<Channel*, bool>::iterator it = other.find(tmp);

	if (msg->params.size() < 1) 
	{
		std::string	tmp = ERR_NEEDMOREPARAMS(client->getNick(), msg->command);
		send(client->getFd(), tmp.c_str(), tmp.size(), 0);
		return;
	}
	if (msg->params[1].empty())
	{
		std::string _topic = tmp->getTopic();
		if (!_topic.empty())
		{
			_topic = RPL_NOTOPIC(client->getNick(), nameChannel);
		}
		else
		{
			_topic = RPL_TOPIC(client->getNick(), nameChannel, _topic);
		}
		
		send(client->getFd(), _topic.c_str(), _topic.size(), 0);
		return;
	}

	std::map<std::string, Client*>    clientsList = tmp->getClients();
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

	if (it == other.end())
		std::cout << "Enter in here" << std::endl;
	if (it->second == false)
	{
		std::string tmp3 = ERR_CHANOPRIVSNEEDED(client->getNick(), nameChannel);
		send(client->getFd(), tmp3.c_str(), tmp3.size(), 0);
		return;
	}

	std::string	params;
	std::vector<std::string>::iterator	it3 = msg->params.begin() + 1;
	for (; it3 != msg->params.end(); it3++) {
		params += *it3;
		if (it3 + 1 != msg->params.end())
			params += " ";
	}

	tmp->setTopic(params);

	std::string	response = "The topic of the channel " + tmp->getName() + " is now " + params + "\r\n";
	send(client->getFd(), response.c_str(), response.size(), 0);

}


