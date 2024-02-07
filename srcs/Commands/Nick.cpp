/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorin <kmorin@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:36:03 by kmorin            #+#    #+#             */
/*   Updated: 2024/02/07 11:08:13 by kmorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Commands/Nick.hpp"

Nick::Nick(void) {}

Nick::~Nick(void) {}

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
 * https://datatracker.ietf.org/doc/html/rfc2812#section-3.1.2
 *
 * This function is responsible for handling the Nick command received from a client.
 * It checks if the nickname parameter is provided and valid, and performs the necessary actions accordingly.
 *
 * If the nickname is empty, ERR_NONICKNAMEGIVEN
 * If the nickname is too long, ERR_ERRONEUSNICKNAME
 * If the nickname is already in use, ERR_NICKNAMEINUSE
 * If the nickname is valid and available, it is set as the client's nickname and send RPL_NICKCHANGE to the client
 *
 * @param server The server object.
 * @param msg The message object containing the command and parameters.
 * @param client The client object.
 */
void	Nick::execute(Server* server, t_Message* msg, Client* client) {
	// the placeholder is used to send the error message to the client if it is not registered
	std::string placeHolder = "*";

	// If the nickname parameter is not provided, an error message is sent to the client.
	if (msg->params.empty()) {
		std::string errEmpty;
		if (client->isRegistered() == true)
			errEmpty = ERR_NONICKNAMEGIVEN(client->getAddress(), client->getNick());
		else
			errEmpty = ERR_NONICKNAMEGIVEN(client->getAddress(), placeHolder);
		client->sendMessage(errEmpty);
		return;
	}

	// If the nickname is too long, an error message is sent to the client.
	std::string	nickname = msg->params[0];

	if (nickname.size() > 9) {
		std::string errSize;
		if (client->isRegistered() == true)
			errSize = ERR_ERRONEUSNICKNAME(client->getAddress(), client->getNick(), nickname);
		else
			errSize = ERR_ERRONEUSNICKNAME(client->getAddress(), placeHolder, nickname);
		client->sendMessage(errSize);
		return;
	}

	// If the nickname is already in use, an error message is sent to the client.
	else if (isNicknameUsed(nickname, server->getClients())) {
		std::string errUsed;
		if (client->isRegistered() == true)
			errUsed = ERR_NICKNAMEINUSE(client->getAddress(), client->getNick(), nickname);
		else
			errUsed = ERR_NICKNAMEINUSE(client->getAddress(), placeHolder, nickname);
		client->sendMessage(errUsed);
		return;
	}

	// If the nickname is valid and available, it is set as the client's nickname.
	else {
		std::string rplNick;
		if (client->isRegistered() == true) {
			std::string	nick = BOLD_TEXT + nickname + RESET;
			rplNick = RPL_NICK(client, nick);
			client->sendMessage(rplNick);
		}
		// std::string	odlNickname = client->getNick();
		client->setNick(nickname);
		//recup les chans ou le client est
		// std::map<Channel*, bool>	chan = client->getChannels();
		//doit changer sur tous les chans ou il est le nom sous lequel il est enregistre dans la map
		// for (std::map<Channel*, bool>::iterator it = chan.begin(); it != chan.end(); ++it) {
			// Channel	*tmp = it->first; //recup l'instance du chan
			// std::map<std::string, Client*> clients = tmp->getClients();
			// std::map<std::string, Client*>::iterator clientOnChan = tmp->getClientIt(odlNickname); //recup un iterator vers l'element lie au client sur ce chan
			// std::cout << clientOnChan->first << " " << clientOnChan->second->getNick() << std::endl;
			// if (clientOnChan != clients.end()) { //si pas fin donc bien present dans chan
				// tmp->addClient(client); //ajoute le client avec le nouveau nick
				// clients.erase(odlNickname); //efface l'ancien element
			// }
		// }
	}
}
