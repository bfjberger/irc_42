/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Execution.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorin <kmorin@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 09:54:28 by kmorin            #+#    #+#             */
/*   Updated: 2024/01/23 15:34:08 by kmorin           ###   ########.fr       */
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

	std::cout << "command: " << msg->command << std::endl;

	ACommand*	cmd = _commands.at(msg->command);

	std::cout << "on est là" << std::endl;

	cmd->execute(msg, client);
}
