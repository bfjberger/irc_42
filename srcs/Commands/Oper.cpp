/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Oper.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorin <kmorin@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:36:05 by kmorin            #+#    #+#             */
/*   Updated: 2024/02/07 15:47:15 by kmorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Commands/Oper.hpp"

Oper::Oper(void) {}

Oper::~Oper(void) {}

/**
 * https://datatracker.ietf.org/doc/html/rfc2812#section-3.1.4
 *
 * Parameters:
 *		<name> <password>
 *
 * assume the name asked is the username of the client asking to be promoted
 * assume the password is the password of the client asking to be promoted
 *
 * If the number of parameters is not valid, ERR_NEEDMOREPARAMS
 * If the password is not the correct one, ERR_PASSWDMISMATCH
 * If the username is not the correct one, nothing is done.
 * If both parameters are correct, we promote the client and send him RPL_YOUREOPER
 *
 * @param server The server object.
 * @param msg The message object containing the command and parameters.
 * @param client The client object.
*/
void	Oper::execute(Server* server, t_Message* msg, Client* client) {

	std::string	response;

	if (msg->params.size() < 2) {
		response = ERR_NEEDMOREPARAMS(client->getAddress(), client->getNick(), msg->command);
		client->sendMessage(response);
	}
	else if (msg->params[1] != server->getPass()) {
		response = ERR_PASSWDMISMATCH(client->getAddress(), client->getNick());
		client->sendMessage(response);
	}
	else if (msg->params[0] != client->getNick()) {
		//no message sent
	}
	else {
		client->setOperator(true);
		response = RPL_YOUREOPER(client->getAddress(), client->getNick());
		client->sendMessage(response);
	}
}
