/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorin <kmorin@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:35:58 by kmorin            #+#    #+#             */
/*   Updated: 2024/01/30 10:32:52 by kmorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Commands/Invite.hpp"

Invite::Invite(void) {}

Invite::~Invite(void) {}

/**
 * ajouter un moyen de savoir si le client a ete invite dans un channel
 * et c'est ca qui devrait etre modifie dans cette commande
 * et cette valeur sera checker dans le join
*/

void	Invite::execute(Server* server, t_Message* msg, Client* client) {

	(void) server;
	(void) client;
	(void) msg;
	std::cout << "invite" << std::endl;
	if (msg->params.size() < 2) 
	{
		std::string	tmp = ERR_NEEDMOREPARAMS(client->getNick(), msg->command);
		send(client->getFd(), tmp.c_str(), tmp.size(), 0);
		return;
	}
	if (!server->getClient(msg->params[0]))
	{
		std::string	tmp = ERR_NOSUCHNICK(client->getNick(), msg->params[0]);
		send(client->getFd(), tmp.c_str(), tmp.size(), 0);
		return;
	}
	
	std::string nameChannel = msg->params[1];

	Channel *channel = server->getChannel(nameChannel);

	std::map<std::string, Client *> clientsList = channel->getClients();
	std::map<std::string, Client *>::iterator it = clientsList.begin();
	for (; it != clientsList.end(); ++it) {
		if (it->first == msg->params[0])
		{
			std::string errOnChannel = ERR_USERONCHANNEL(client->getNick(), msg->params[0], nameChannel);
		send(client->getFd(), errOnChannel.c_str(), errOnChannel.size(), 0);
		return;
		}
			break;
	}
	it = clientsList.begin();
	for (; it != clientsList.end(); ++it) 
	{
		if (it->first == client->getNick())
		{
			break;
		}
	}
	if (it == clientsList.end())
	{
			std::string errNotOnChannel = ERR_NOTONCHANNEL(client->getNick(), nameChannel);
			send(client->getFd(), errNotOnChannel.c_str(), errNotOnChannel.size(), 0);
			return;
	}

	std::map<Channel *, bool> other = client->getChannels();
	std::map<Channel *, bool>::iterator it_2 = other.find(channel);
	if (it_2 == other.end()) {
		std::cout << COLOR("red", "ERROR: ") << "Client " << client->getNick() << " is not in channel " << nameChannel << std::endl;
		return;
	}
	if (it_2->second == false) {
		std::string errNotOperator = ERR_CHANOPRIVSNEEDED(client->getNick(), nameChannel);
		send(client->getFd(), errNotOperator.c_str(), errNotOperator.size(), 0);
		return;
	}

	std::string rpl_invit = RPL_INVITING(it->first, nameChannel, client->getNick()); 
	send(it->second->getFd(), rpl_invit.c_str(), rpl_invit.size(), 0);
	rpl_invit = "An invitation has been sent to " + it->first + "\r\n";
	send(client->getFd(), rpl_invit.c_str(), rpl_invit.size(), 0);

	channel->setInvitedClientVector(it->first);
	




}

// - Paramètres:
//     - `<nickname> <channel>`
// - utiliser pour inviter un user, identifié par `<nickname>`, sur un channel, identifié par `<channel>`
// - il n’y a pas de conditions sur l’existence ou la validité du channel où l’on invite ce user
// - pour inviter un user sur un channel en invite only, le client envoyant cette commande doit être un channel operator sur ce channel





