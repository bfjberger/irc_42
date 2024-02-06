/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorin <kmorin@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:36:07 by kmorin            #+#    #+#             */
/*   Updated: 2024/02/06 09:26:07 by kmorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Commands/Pass.hpp"

Pass::Pass(void) {}

Pass::~Pass(void) {}

/**
 * https://datatracker.ietf.org/doc/html/rfc2812#section-3.1.1
 *
 * Parameter:
 * 		<password>
 *
 * If the number of parameter is not valid, the corresponding error message is sent to the client.
 * If the client is already registered, the corresponding error message is sent to the client.
 * Else it sets the parameter as the password associated to the client
 *
 * @param server The server object.
 * @param msg The message oject containing the command and parameters.
 * @param client The client object.
*/
void	Pass::execute(Server* server, t_Message* msg, Client* client) {

	(void) server;

	std::string response;

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
		client->setPass(msg->params[0]);
	}
}
