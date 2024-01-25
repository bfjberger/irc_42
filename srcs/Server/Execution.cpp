/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Execution.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorin <kmorin@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 09:54:28 by kmorin            #+#    #+#             */
/*   Updated: 2024/01/25 09:19:41 by kmorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

/*
	! * msg is new
*/
void	Server::execCommand(t_Message* msg, Client* client) {

	(void) msg;
	(void) client;

	if (msg->command[0] == '/')
		msg->command = msg->command.erase(0, 1);

	if (msg->command.empty())
		return;

	for (size_t i = 0; i < msg->command.size(); i++)
		msg->command[i] = toupper(msg->command[i]);

	// Compare the command with the map of commands and return if not found
	if (_commands.find(msg->command) == _commands.end()) {

		std::string tmp = ERR_UNKNOWNCOMMAND(client->getNick(), msg->command);
		send(client->getFd(), tmp.c_str(), tmp.size(), 0);

		return;
	}

	ACommand*	cmd = _commands.at(msg->command);

	cmd->execute(this, msg, client);

	delete msg;
}
