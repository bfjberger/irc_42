/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParserUtils.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorin <kmorin@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 14:17:00 by kmorin            #+#    #+#             */
/*   Updated: 2024/01/26 13:11:19 by kmorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

std::string	tmpFormatString(std::string msg) {

	if (msg.find(' ') != std::string::npos && msg.find(' ') == 0)
		msg.erase(msg.find(' '), 1);

	if (msg.find('\r') != std::string::npos)
		msg.erase(msg.find('\r'), 1);

	return (msg);
}

void	Server::parsePrefix(std::string &message, t_Message* msg, Client* client) {

	msg->prefix = message.substr(1, message.find(' ') - 1);

	if (msg->prefix != client->getNick()) {
		std::string	tmp = "Invalid prefix in " + message + "\n";
		send(client->getFd(), tmp.c_str(), tmp.size(), 0);
		msg->error = true;
	}
	else {
		msg->hasPrefix = true;
		message.erase(0, message.find(' ') + 1);
	}
}

// a function that trim the string from any carriage return and new line
void	trimString(std::string &str) {

	if (str.find('\r') != std::string::npos)
		str.erase(str.find('\r'), 1);

	if (str.find('\n') != std::string::npos)
		str.erase(str.find('\n'), 1);
}

/*
	! * cherche (et trouve) que le \n à la fin de l'input,
	! * si il y en a avant, ce n'est pas pris en compte
*/
void	Server::splitMessage(std::vector<std::string> &cmds, std::string msg) {

	size_t		pos = 0;
	std::string	delimiter = "\n";
	std::string	substr;

	while ((pos = msg.find(delimiter)) != msg.npos) {
		substr = msg.substr(0, pos);
		cmds.push_back(substr);
		msg.erase(0, pos + delimiter.length());
	}

	// // show parsed message
	// for (size_t i = 0; i != cmds.size(); i++) {
	// 	std::cout << "cmds[" << i << "]: " << cmds[i] << std::endl;
	// }
}
