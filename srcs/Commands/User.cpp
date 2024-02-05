/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorin <kmorin@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:36:12 by kmorin            #+#    #+#             */
/*   Updated: 2024/02/05 11:36:16 by kmorin           ###   ########.fr       */
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
 * If the number of parameters is not valid, the corresponding error message is sent to the client.
 * If the client is already registered, the correspond error message is sent.
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
		response = ERR_NEEDMOREPARAMS(client->getNick(), msg->command);
		client->sendMessage(response);
	}
	else if (client->isRegistered()) {
		response = ERR_ALREADYREGISTRED(client->getNick());
		client->sendMessage(response);
	}
	else {
		msg->params[0] = tmpFormatString(msg->params[0]);
		client->setUserName(msg->params[0]);
	}
}
