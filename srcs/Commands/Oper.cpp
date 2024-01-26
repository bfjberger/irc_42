/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Oper.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorin <kmorin@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:36:05 by kmorin            #+#    #+#             */
/*   Updated: 2024/01/26 15:56:25 by kmorin           ###   ########.fr       */
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
 * If the number of parameters is not valid, the corresponding error message is sent to the client.
 * If the password is not the correct one, the corresponding error message is sent to the client.
 * If the username is not the correct one, nothing is done.
 * If both parameters are correct, we promote the client and send him the corresponding message.
 *
 * @param server The server object.
 * @param msg The message object containing the command and parameters.
 * @param client The client object.
*/
void	Oper::execute(Server* server, t_Message* msg, Client* client) {

	if (msg->params.size() < 2) {
		std::string tmp = ERR_NEEDMOREPARAMS(client->getNick(), msg->command);
		send(client->getFd(), tmp.c_str(), tmp.size(), 0);
	}
	else if (msg->params[1] != server->getPass()) {
		std::string	tmp = ERR_PASSWDMISMATCH(client->getNick());
		send(client->getFd(), tmp.c_str(), tmp.size(), 0);
	}
	else if (msg->params[0] != client->getUserName()) {
		//no message sent
	}
	else {
		client->setOperator(true);
		std::string	tmp = RPL_YOUREOPER(client->getNick());
		send(client->getFd(), tmp.c_str(), tmp.size(), 0);
	}
}
