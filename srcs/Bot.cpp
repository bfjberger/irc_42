/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorin <kmorin@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 16:28:48 by kmorin            #+#    #+#             */
/*   Updated: 2024/02/06 09:28:15 by kmorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bot.hpp"

/* -------------------------------------------------------------------------- */
/*                           CONSTRUCTOR/DESTRUCTOR                           */
/* -------------------------------------------------------------------------- */

Bot::Bot(int fd) : _fd(fd),
					_name("bot") {

}

Bot::~Bot(void) {}

/* ************************************************************************** */
/*                                   GETTERS                                  */
/* ************************************************************************** */

int	Bot::getFd() const {
	return (_fd);
}

const std::string&	Bot::getName() const {
	return (_name);
}

const struct sockaddr_in&	Bot::getBotAddress() const {
	return (_botAddress);
}

/* ************************************************************************** */
/*                               MEMBER FUNCTIONS                             */
/* ************************************************************************** */

void	Bot::handleBot(Server* server, t_Message* msg, Client* client) {

	Bot* target = server->getBot();

	std::string	rplMsg;
	std::string rplPrivmsg;

	if (msg->params[1][0] == ':')
		msg->params[1].erase(0, 1);

	if (msg->params.size() == 1 || (msg->params[1] != "HOUR" && msg->params[1] != "STAT")) {
		rplMsg = "This awesome bot can give the time with HOUR and some stats about our awesome server with STAT.";
	}
	else if (msg->params[1] == "HOUR") {
		std::time_t	result = std::time(nullptr);
		rplMsg = std::asctime(std::localtime(&result));
		rplMsg.erase(rplMsg.size() - 1);
	}
	else if (msg->params[1] == "STAT") {
		// There are currently + server->getChannels().size() + channels and + server->getClients().size() + users on the server.
		std::stringstream	ssChan;
		ssChan << static_cast<int>(server->getChannels().size());
		std::stringstream	ssClient;
		ssClient << static_cast<int>(server->getClients().size());
		rplMsg = "There are currently " + ssChan.str() + " channels and " + ssClient.str() + " users on the server.";
	}

	// rplMsg = ":" + rplMsg;
	// rplPrivmsg = RPL_PRIVMSG(client, target->getName(), rplMsg);
	rplPrivmsg = RPL_PRIVMSG(client->getAddress(), getName(), rplMsg);
	std::cout << COLOR("[" << client->getNick() << "] -> [" << target->getName() << "] : " << rplMsg, GREEN) << std::endl;
	client->sendMessage(rplPrivmsg);
}
