/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorin <kmorin@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 09:01:38 by kmorin            #+#    #+#             */
/*   Updated: 2024/01/24 16:24:09 by kmorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

std::string	tmpFormatString(std::string msg) {

	if (msg.find(' ') != std::string::npos && msg.find(' ') == 0)
		msg.erase(msg.find(' '), 1);

	if (msg.find('\r') != std::string::npos)
		msg.erase(msg.find('\r'), 1);

	return msg;
}

// a function that trim the string from any carriage return and new line
void	trimString(std::string &str) {

	if (str.find('\r') != std::string::npos)
		str.erase(str.find('\r'), 1);

	if (str.find('\n') != std::string::npos)
		str.erase(str.find('\n'), 1);
}

void	Server::parsePrefix(std::string &message, t_Message* msg, Client* client) {

	msg->prefix = message.substr(1, message.find(' ') - 1);

	if (msg->prefix != client->getNick()) {
		std::cout << COLOR("Invalid prefix in ", RED) << message << COLOR(" from Client #", RED) << client->getFd() << std::endl;
		msg->wrongPrefix = true;
	}
	else {
		msg->hasPrefix = true;
		message.erase(0, message.find(' ') + 1);
	}
}

// TODO: revoir les autres conditions de parsing (parsePrefix semble OK)
t_Message*	Server::parseCommands(std::string message, Client* client) {

	t_Message*	msg = new t_Message;

	msg->hasPrefix = false;
	msg->hasCommand = false;
	msg->wrongPrefix = false;

	trimString(message);

	// If the first word of the message has a ':' in the first char then it is a prefix
	if (message[0] == ':') {
		parsePrefix(message, msg, client);
		if (msg->wrongPrefix == true)
			return (msg);
	}

	// Parse the command into msg.command and erase it from the message
	if (message.find(' ') != std::string::npos) {

		msg->command = message.substr(0, message.find(' '));
		message.erase(0, message.find(' ') + 1);
		if (msg->command == "" || msg->command == "\r")
			msg->hasCommand = false;
		else
			msg->hasCommand = true;
	}

	// Parse the params into msg.params and erase it from the message
	while (message.find(' ') != std::string::npos) {
		msg->params.push_back(message.substr(0, message.find(' ')));
		message.erase(0, message.find(' ') + 1);
	}

	if (message.length() != 0 && message.find(' ') == message.npos) {
		msg->params.push_back(message.substr(0));
		message.erase(0, message.length());
	}

	return (msg);
}

void	Server::fillUserInfo(std::map<int, Client *> &clients, int clientSocketFd, std::string msg) {

	std::map<int, Client *>::iterator it = clients.find(clientSocketFd);
	(void)clients, (void)clientSocketFd;

	trimString(msg);
	std::cout << "fillUserInfo msg: |" << msg << "|" << std::endl;
	if (msg.find("NICK") != std::string::npos || msg.find("nick") != std::string::npos) {
		msg = tmpFormatString(msg);
		it->second->setNick(msg.substr(msg.find("NICK") + 5));
	}
	else if (msg.find("USER") != std::string::npos || msg.find("user") != std::string::npos) {
		msg = tmpFormatString(msg);
		//  setUSER by parsing the msg just after USER and before the first space
		it->second->setUserName(msg.substr(msg.find("USER") + 5, msg.find(' ')));
		// setRealName by parsing the msg just after the first :
		if (msg.find(':') != std::string::npos)
			it->second->setRealName(msg.substr(msg.find(':') + 1));
	}
	else if (msg.find("PASS") != std::string::npos || msg.find("pass") != std::string::npos) {
		msg = tmpFormatString(msg);
		it->second->setPass(msg.substr(msg.find("PASS") + 5));
	}
}

void	Server::splitMessage(std::vector<std::string> &cmds, std::string msg) {

	int pos = 0;
	std::string delimiter = "\n";
	std::string substr;

	while ((pos = msg.find(delimiter)) != static_cast<int>(std::string::npos)) {
		substr = msg.substr(0, pos);
		cmds.push_back(substr);
		msg.erase(0, pos + delimiter.length());
	}

	// // show parsed message
	// for (size_t i = 0; i != cmds.size(); i++) {
	// 	std::cout << "cmds[" << i << "]: " << cmds[i] << std::endl;
	// }
}

// Fill registration info if the client is not yet registered
// Parse the commands if he is
void	Server::parser(std::string message, int clientSocketFd) {

	t_Message*								msg;
	std::vector<std::string>				cmds;
	std::map<int, Client *>::iterator	it = _clients.find(clientSocketFd);

	splitMessage(cmds, message);

	for (size_t i = 0; i != cmds.size(); i++) {
		if (it->second->isRegistered() == false) {

			fillUserInfo(_clients, clientSocketFd, cmds[i]);

			if (it->second->getPass() == _password)
				it->second->setLogged(true);

			if (it->second->getNick() != "" && it->second->getUserName() != "")
				it->second->setReceivedInfo(true);

			if (it->second->isLogged() == true && it->second->hasReceivedInfo() == true && it->second->welcomeSent() == false) {
				it->second->setRegistered(true);
				std::string welcome = RPL_WELCOME(it->second->getNick(), _name, USER_ID(it->second));
				send(clientSocketFd, welcome.c_str(), welcome.length(), 0);
			}

			it->second->printInfo();
		}
		else {
			msg = parseCommands(message, it->second);
			if (msg->wrongPrefix == true) {
				delete msg;
				return ;
			}
			else
				execCommand(msg, it->second);
		}
	}
	// it->second.printInfo();
}
