/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Execution.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorin <kmorin@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 09:54:28 by kmorin            #+#    #+#             */
/*   Updated: 2024/02/01 15:06:44 by kmorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

/*
	! * msg is new
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
		if (client->isInChannel() == true) {
			Channel* channel = getChannel(client->getCurrentChannel());
			if (channel != NULL) {
				channel->sendToAllButOne(message, client, ISINCHANNEL);
			}
		}
		else if (msg->command == "PING")
		{
			std::string pongMsg = ":" + RPL_PONG(USER_ID(client), msg->params[0]);
			client->sendMessage(pongMsg, 0);
		}
		else if (msg->command == "PONG")
		{
			std::string pongMsg = ":" + RPL_PING(USER_ID(client), msg->params[0]);
			client->sendMessage(pongMsg, 0);
		}
		else if (msg->command == "STOP") {
			g_server_running = false;
		}
		else {
			std::string tmp = ERR_UNKNOWNCOMMAND(client->getNick(), msg->command);
			send(client->getFd(), tmp.c_str(), tmp.size(), 0);
		}
	}
	else {
		ACommand*	cmd = _commands.at(msg->command);
		cmd->execute(this, msg, client);
	}

	delete msg;
}
