/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorin <kmorin@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:36:07 by kmorin            #+#    #+#             */
/*   Updated: 2024/01/26 11:40:41 by kmorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Commands/Pass.hpp"

Pass::Pass(void) {}

Pass::~Pass(void) {}

void	Pass::execute(Server* server, t_Message* msg, Client* client) {

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
		client->setPass(msg->params[0]);
	}
}
