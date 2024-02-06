/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorin <kmorin@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:36:12 by kmorin            #+#    #+#             */
/*   Updated: 2024/02/06 10:39:36 by kmorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Commands/User.hpp"

User::User(void) {}

User::~User(void) {}

/**
 * https://datatracker.ietf.org/doc/html/rfc2812#section-3.1.3
 *
 * Parameters:
 *		<user>
 *
 * If the number of parameters is not valid, ERR_NEEDMOREPARAMS
 * If the client is already registered, ERR_ALREADYREGISTRED
 * If the username is valid and available, it is set as the client's username.
 *
 * @param server The server object.
 * @param msg The message object containing the command and parameters.
 * @param client The client object.
*/
void	User::execute(Server* server, t_Message* msg, Client* client) {

	(void) server;

	std::string	response;

	if (msg->params.empty()) {
		response = ERR_NEEDMOREPARAMS(client->getAddress(), client->getNick(), msg->command);
		client->sendMessage(response);
	}
	else if (client->isRegistered()) {
		response = ERR_ALREADYREGISTRED(client->getAddress(), client->getNick());
		client->sendMessage(response);
	}
	else {
		msg->params[0] = tmpFormatString(msg->params[0]);
		client->setUserName(msg->params[0]);
	}
}
