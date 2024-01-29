/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorin <kmorin@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:36:02 by kmorin            #+#    #+#             */
/*   Updated: 2024/01/29 17:18:47 by kmorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Commands/Mode.hpp"

Mode::Mode(void) {}

Mode::~Mode(void) {}

/**
 * https://datatracker.ietf.org/doc/html/rfc2812#section-3.1.5 USER MODE
 * https://datatracker.ietf.org/doc/html/rfc2812#section-3.2.3 CHANNEL MODE
 *
 * Parameters USER mode:
 * 		<nickname> {[+|-]|o}
 *
 * Parameters CHANNEL mode:
 * 		<channel> {[+|-]|i|t|k|o|l} [<topic>] [<key>] [<user>] [<limit>]
 *
 * @param server The server object.
 * @param msg The message object containing the command and parameters.
 * @param client The client object.
*/

void	Mode::channelMode(Server* server, t_Message* msg, Client* client) {

	std::string	nameChannel = msg->params[0];

	Channel*	channel = server->getChannel(nameChannel);

	if (!channel) {
		std::string	response = ERR_NOSUCHCHANNEL(client->getNick(), nameChannel);
		send(client->getFd(), response.c_str(), response.size(), 0);
		return;
	}

	std::map<Channel*, bool>			chans = client->getChannels();
	std::map<Channel*, bool>::iterator	it = chans.find(channel);

	if (it->second == false) { // the user is not channel operator
		std::string	response = ERR_CHANOPRIVSNEEDED(client->getNick(), nameChannel);
		send(client->getFd(), response.c_str(), response.size(), 0);
		return;
	}
	else if (msg->params.size() == 1) { // print info
		std::string	response;
		std::string	modes;
		if (channel->getI())
			modes += "+i";
		if (channel->getK())
			modes += "k";
		if (channel->getL())
			modes += "l";
		response = RPL_CHANNELMODEIS(nameChannel, modes);
		send(client->getFd(), response.c_str(), response.size(), 0);
	}
	else if (!msg->params[1].compare("+i")) {

	}
	else if (!msg->params[1].compare("-i")) {

	}
	else if (!msg->params[1].compare("+t")) {

	}
	else if (!msg->params[1].compare("-t")) {

	}
	else if (!msg->params[1].compare("+k")) {

	}
	else if (!msg->params[1].compare("-k")) {

	}
	else if (!msg->params[1].compare("+o")) {

	}
	else if (!msg->params[1].compare("-o")) {

	}
	else if (!msg->params[1].compare("+l")) {

	}
	else if (!msg->params[1].compare("-l")) {

	}
	else { // unknown mode
		std::string	response = ERR_UNKNOWNMODE(client->getNick(), msg->params[1]);
		send(client->getFd(), response.c_str(), response.size(), 0);
	}
}

void	Mode::userMode(Server* server, t_Message* msg, Client* client) {

	std::map<int, Client*>	clients = server->getClients();

	std::map<int, Client*>::const_iterator it;
	for (it = clients.begin(); it != clients.end(); ++it) {
		if (it->second->getNick() == msg->params[0])
			break;
	}

	if (it == clients.end()) { // couldn't find a user
		std::string	response = ERR_USERSDONTMATCH(client->getNick());
		send(client->getFd(), response.c_str(), response.size(), 0);
	}
	else if (msg->params.size() == 1) { // print info
		std::string	response;
		if (client->isOperator())
			response = RPL_UMODEIS(client->getNick(), "+o");
		else
			response = RPL_UMODEIS(client->getNick(), "-o");
		send(client->getFd(), response.c_str(), response.size(), 0);
	}
	else if (!msg->params[1].compare("+o")) {
		//ignore
	}
	else if (!msg->params[1].compare("-o")) { // demote an operator
		std::string	response;
		if (client->isOperator()) {
			client->setOperator(false);
			response = "You're now no longer an operator !\r\n";
		}
		else
			response = "lol from the start you're not an operator !\r\n";
		send(client->getFd(), response.c_str(), response.size(), 0);
	}
	else { // unknown mode
		std::string	response = ERR_UMODEUNKNOWNFLAG(client->getNick());
		send(client->getFd(), response.c_str(), response.size(), 0);
	}
}

void	Mode::execute(Server* server, t_Message* msg, Client* client) {

	if (msg->params.size() < 1) {
		std::string	response = ERR_NEEDMOREPARAMS(client->getNick(), msg->command);
		send(client->getFd(), response.c_str(), response.size(), 0);
		return;
	}

	if (msg->params[0][0] == '#')
		channelMode(server, msg, client);
	else
		userMode(server, msg, client);
}
