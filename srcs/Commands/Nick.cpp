/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorin <kmorin@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:36:03 by kmorin            #+#    #+#             */
/*   Updated: 2024/01/24 14:05:24 by kmorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Commands/Nick.hpp"

Nick::Nick(void) {}

Nick::~Nick(void) {}

// https://datatracker.ietf.org/doc/html/rfc2813
// https://datatracker.ietf.org/doc/html/rfc2812#section-3.1.2

bool isNicknameUsed(const std::string& nickname, const std::map<int, Client*>& clients) {
	std::map<int, Client*>::const_iterator it;
	for (it = clients.begin(); it != clients.end(); ++it) {
		if (it->second->getNick() == nickname) {
			return true; // Nickname is already used
		}
	}
	return false; // Nickname is not used
}

/**
 * Executes the Nick command.
 * This function is responsible for handling the Nick command received from a client.
 * It checks if the nickname parameter is provided and valid, and performs the necessary actions accordingly.
 * If the nickname is empty, an error message is sent to the client.
 * If the nickname is too long, an error message is sent to the client.
 * If the nickname is already in use, an error message is sent to the client.
 * If the nickname is valid and available, it is set as the client's nickname.
 *
 * @param server The server object.
 * @param msg The message object containing the command and parameters.
 * @param client The client object.
 */
void	Nick::execute(Server* server, t_Message* msg, Client* client) {

	std::string placeHolder = "*";

	if (msg->params.empty()) {
		std::string errEmpty;
		if (client->isLogged() == true)
			errEmpty = ERR_NONICKNAMEGIVEN(client->getNick());
		else
			errEmpty = ERR_NONICKNAMEGIVEN(placeHolder);
		send(client->getFd(), errEmpty.c_str(), errEmpty.size(), 0);
		std::cout << COLOR("Send to client: ", CYAN) << errEmpty << std::endl;
		return;
	}

	std::string nickname = msg->params[0];

	if (nickname.size() > 9) {
		std::string errSize;
		if (client->isLogged() == true)
			errSize = ERR_ERRONEUSNICKNAME(client->getNick(), nickname);
		else
			errSize = ERR_ERRONEUSNICKNAME(placeHolder, nickname);
		send(client->getFd(), errSize.c_str(), errSize.size(), 0);
		std::cout << COLOR("Send to client: ", CYAN) << errSize << std::endl;
		return;
	} 
	
	else if (isNicknameUsed(nickname, server->getClients())) {
		std::string errUsed;
		if (client->isLogged() == true)
			errUsed = ERR_NICKNAMEINUSE(client->getNick(), nickname);
		else
			errUsed = ERR_NICKNAMEINUSE(placeHolder, nickname);
		send(client->getFd(), errUsed.c_str(), errUsed.size(), 0);
		std::cout << COLOR("Send to client: ", CYAN) << errUsed << std::endl;
		return;
	} 
	
	else {
		std::string rplNick;
		if (client->isLogged() == true) {
			rplNick = RPL_NICKCHANGE(client->getNick(), nickname);
			send(client->getFd(), rplNick.c_str(), rplNick.size(), 0);
			std::cout << COLOR("Send to client: ", CYAN) << rplNick << std::endl;
		}
		client->setNick(nickname);
	}
}
