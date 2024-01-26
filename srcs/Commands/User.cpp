/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorin <kmorin@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:36:12 by kmorin            #+#    #+#             */
/*   Updated: 2024/01/26 11:50:54 by kmorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Commands/User.hpp"

User::User(void) {}

User::~User(void) {}

void	User::execute(Server* server, t_Message* msg, Client* client) {

	(void) server;

	if (msg->params.empty()) {
		std::string tmp = ERR_NEEDMOREPARAMS(client->getNick(), msg->command);
		send(client->getFd(), tmp.c_str(), tmp.size(), 0);
	}
	else if (client->isRegistered()) {
		std::string	tmp = ERR_ALREADYREGISTRED(client->getNick());
		send(client->getFd(), tmp.c_str(), tmp.size(), 0);
	}
	else {
		msg->params[0] = tmpFormatString(msg->params[0]);
		client->setUserName(msg->params[0]);
	}
}
