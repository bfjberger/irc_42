/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorin <kmorin@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 09:01:38 by kmorin            #+#    #+#             */
/*   Updated: 2024/01/26 14:15:25 by kmorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void	Server::fillUserInfo(std::map<int, Client *>::iterator &it, std::string message) {

	t_Message*	msg;

	msg = parseCommands(message, it->second);
	if (msg->error == true) {
		delete msg;
		return ;
	}

	trimString(message);

	std::cout << std::endl << "fillUserInfo msg: |" << message << "|" << std::endl;

	if (!msg->command.compare("PASS"))
		_commands[msg->command]->execute(this, msg, it->second);

	if (!msg->command.compare("USER"))
		_commands[msg->command]->execute(this, msg, it->second);

	if (!msg->command.compare("NICK"))
		_commands[msg->command]->execute(this, msg, it->second);

	delete msg;
}

t_Message*	Server::parseCommands(std::string message, Client* client) {

	t_Message*	msg = new t_Message;

	msg->hasPrefix = false;
	msg->hasCommand = false;
	msg->error = false;

	trimString(message);

	// If the first word of the message has a ':' in the first char then it is a prefix
	if (message[0] == ':') {
		parsePrefix(message, msg, client);
		if (msg->error == true)
			return (msg);
	}

	// Parse the command into msg.command
	if (message.find(' ') != std::string::npos) {
		msg->command = message.substr(0, message.find(' '));
		message.erase(0, message.find(' ') + 1);
	}
	else {
		msg->command = message;
		message.erase(0);
	}

	if (msg->command == "\r" || msg->command.empty())
		msg->error = true;

	if (msg->command[0] == '/')
		msg->command = msg->command.erase(0, 1);

	// Put the command in uppercase
	for (size_t i = 0; i < msg->command.size(); i++)
		msg->command[i] = toupper(msg->command[i]);

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

// Fill registration info if the client is not yet registered
// Parse the commands if the client is already registered
void	Server::parser(std::string message, int clientSocketFd) {

	std::vector<std::string>			cmds;
	std::map<int, Client *>::iterator	it = _clients.find(clientSocketFd);

	if (message.empty() == true || message == "\n")
		return ;
	splitMessage(cmds, message);

	if (message.find("CAP") != std::string::npos) {
		std::string msg = ": CAP * LS :\r\n";
		send(clientSocketFd, msg.c_str(), msg.length(), 0);
		_capStatus = true;
		return ;
	}
	if (_capStatus == true && message.find("CAP END") != std::string::npos) {
		std::cout << "CAP END" << std::endl;
		_capStatus = false;
		return ;
	}

	for (size_t i = 0; i != cmds.size(); i++) {

		if (it->second->isRegistered() == false) {

			fillUserInfo(it, cmds[i]);

			if (it->second->getPass() == _password)
				it->second->setLogged(true);

			if (it->second->getNick() != "" && it->second->getUserName() != "")
				it->second->setReceivedInfo(true);

			if (it->second->isLogged() == true && it->second->hasReceivedInfo() == true && it->second->welcomeSent() == false) {
				it->second->setRegistered(true);
				std::string welcome = RPL_WELCOME(it->second->getNick(), _name, USER_ID(it->second));
				send(clientSocketFd, welcome.c_str(), welcome.length(), 0);
				it->second->setWelcomeSent(true);
			}

			it->second->printInfo();
		}
		else
			execCommand(cmds[i], it->second);
	}
}
