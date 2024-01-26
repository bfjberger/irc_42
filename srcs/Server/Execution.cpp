/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Execution.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorin <kmorin@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 09:54:28 by kmorin            #+#    #+#             */
/*   Updated: 2024/01/26 13:19:54 by kmorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

/*
	! * msg is new

	voir comment gérer le / si ca convient avec le fillUserInfo()
*/
void	Server::execCommand(std::string message, Client* client) {


	t_Message*	msg;

	msg = parseCommands(message, client);
	if (msg->error == true) {
		delete msg;
		return ;
	}

	// Compare the command with the map of commands and return if not found
	if (_commands.find(msg->command) == _commands.end()) {
		std::string tmp = ERR_UNKNOWNCOMMAND(client->getNick(), msg->command);
		send(client->getFd(), tmp.c_str(), tmp.size(), 0);
	}
	else {
		ACommand*	cmd = _commands.at(msg->command);
		cmd->execute(this, msg, client);
	}

	delete msg;
}
