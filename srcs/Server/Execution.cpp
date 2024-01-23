/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Execution.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorin <kmorin@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 09:54:28 by kmorin            #+#    #+#             */
/*   Updated: 2024/01/23 10:57:04 by kmorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void	Server::execCommand(t_Message msg, Client client) {

	(void) msg;
	(void) client;
	std::cout << "on est la" << std::endl;
	// std::string	cmds[13] = {"PASS", "NICK", "USER", "JOIN", "OPER", "MODE", "QUIT", "TOPIC", "INVITE", "KICK", "PRIVMSG", "KILL", "PART"};

	// int	i = 0;

	// while (i < 13) {

	// 	if (msg.command == cmds[i])
	// 		break;
	// 	i++;
	// }

	// ACommand*	cmd;

	// switch (i + 1) {

	// 	case 1: execute(msg, client); break;

	// 	case 2: execute(msg, client); break;

	// 	case 3: execute(msg, client); break;

	// 	case 4: execute(msg, client); break;

	// 	case 5: execute(msg, client); break;

	// 	case 6: execute(msg, client); break;

	// 	case 7: execute(msg, client); break;

	// 	case 8: execute(msg, client); break;

	// 	case 9: execute(msg, client); break;

	// 	case 10: execute(msg, client); break;

	// 	case 11: execute(msg, client); break;

	// 	case 12: execute(msg, client); break;

	// 	case 13: execute(msg, client); break;

	// 	default:
	// 		std::cout << COLOR(ERR_UNKNOWNCOMMAND(msg.command), RED) << std::endl;
	// 		break;
	// }
}
