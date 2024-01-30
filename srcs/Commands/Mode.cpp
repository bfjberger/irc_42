/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorin <kmorin@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:36:02 by kmorin            #+#    #+#             */
/*   Updated: 2024/01/30 13:36:04 by kmorin           ###   ########.fr       */
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
 * you can't remove the topic, only change it with +t
 *
 * @param server The server object.
 * @param msg The message object containing the command and parameters.
 * @param client The client object.
*/

// TODO send the successful modification of a channel to the channel
// TODO send the failed modification of a channel to the client requesting the changes

void	Mode::handleInvit(Server* server, t_Message* msg, Client* client, Channel* channel) {

	(void) server;
	(void) msg;

	if (!msg->params[1].compare("+i")) {
		channel->setI(true);
		std::string	response = "The channel " + channel->getName() + " is now in invite-only mode.\r\n";
		send(client->getFd(), response.c_str(), response.size(), 0);
	}
	else {
		channel->setI(false);
		std::string	response = "The channel " + channel->getName() + " is no longer in invite-only mode.\r\n";
		send(client->getFd(), response.c_str(), response.size(), 0);
	}
}

void	Mode::handleTopic(Server* server, t_Message* msg, Client* client, Channel* channel) {

	(void) server;
	(void) client;

	std::string	params;
	std::vector<std::string>::iterator	it = msg->params.begin() + 2;
	for (; it != msg->params.end(); it++) {
		params += *it;
		if (it + 1 != msg->params.end())
			params += " ";
	}

	channel->setTopic(params);

	std::string	response = "The topic of the channel " + channel->getName() + " is now " + params + "\r\n";
	send(client->getFd(), response.c_str(), response.size(), 0);
}

void	Mode::handleKey(Server* server, t_Message* msg, Client* client, Channel* channel) {

	(void) server;

	if (!msg->params[1].compare("+k") && !channel->getPassword().empty()) { //set the key and the key is not yet set
		channel->setK(true);
		channel->setPassword(msg->params[2]);
		std::string	response = "A key was successfully setup for the channel " + channel->getName() + " by " + client->getNick() + "\r\n";
		send(client->getFd(), response.c_str(), response.size(), 0);
	}
	else if (!msg->params[1].compare("+k") && channel->getPassword().empty()) { //set the key and the key is already set
		std::string	response = ERR_KEYSET(client->getNick(), channel->getName());
		send(client->getFd(), response.c_str(), response.size(), 0);
	}
	else { //remove the key
		channel->setK(false);
		channel->setPassword("");
		std::string	response = "The key was successfully removed for the channel " + channel->getName() + " by " + client->getNick() + "\r\n";
		send(client->getFd(), response.c_str(), response.size(), 0);
	}
}

void	Mode::handleChanOp(Server* server, t_Message* msg, Client* client, Channel* channel) {

	(void) server;

	Client*	clientChanging = channel->getClient(msg->params[2]);
	if (!clientChanging) {
		std::string	response = ERR_USERNOTINCHANNEL(client->getNick(), msg->params[2], channel->getName());
		send(client->getFd(), response.c_str(), response.size(), 0);
		return;
	}

	std::map<Channel*, bool>	chanList = client->getChannels();
	std::map<Channel*, bool>::iterator it = chanList.find(channel);

	if (!msg->params[1].compare("+o")) {
		it->second = true;
		std::string	response = "You promoted " + clientChanging->getNick() + " to channel operator of channel " + channel->getName() + "\r\n";
		send(client->getFd(), response.c_str(), response.size(), 0);
	}
	else if (clientChanging->getFd() == client->getFd()) {
		it->second = false;
		std::string	response = "You demoted yourself from channel operator of the channel " + channel->getName() + "\r\n";
		send(client->getFd(), response.c_str(), response.size(), 0);
	}
	else {
		std::string	response = "You cannot demote an another channel operator.\r\n";
		send(client->getFd(), response.c_str(), response.size(), 0);
	}
}

void	Mode::handleLimit(Server* server, t_Message* msg, Client* client, Channel* channel) {

	(void) server;

	if (!msg->params[1].compare("+l")) {
		if (msg->params.size() >= 3) {
			channel->setL(true);
			std::stringstream tmp(msg->params[2]);
			int	limit;
			tmp >> limit;
			if (tmp.fail()) {
				std::string	response = "Failed to set the limit of users on channel " + channel->getName() + ". It takes an int as value.\r\n";
				send(client->getFd(), response.c_str(), response.size(), 0);
			}
			else {
				channel->setUserLimit(limit);
				std::string	response = "The channel " + channel->getName() + " now has a limit of " + msg->params[2] + " users.\r\n";
				send(client->getFd(), response.c_str(), response.size(), 0);
			}
		}
		else {
			std::string	response = ERR_NEEDMOREPARAMS(client->getNick(), msg->command);
			send(client->getFd(), response.c_str(), response.size(), 0);
		}
	}
	else {
		channel->setL(false);
		channel->setUserLimit(-1);
		std::string	response = "The channel " + channel->getName() + " no longer has a user limit.\r\n";
		send(client->getFd(), response.c_str(), response.size(), 0);
	}
}

void	Mode::channelMode(Server* server, t_Message* msg, Client* client) {

	std::string	nameChannel = msg->params[0];

	Channel*	channel = server->getChannel(nameChannel);

	if (!channel) {
		std::string	response = ERR_NOSUCHCHANNEL(client->getNick(), nameChannel);
		send(client->getFd(), response.c_str(), response.size(), 0);
		return;
	}

	if (msg->params.size() == 1) { // print info (no need for privileges so done before those checks)
		std::string	response;
		std::string	modes = "+";
		if (channel->getI())
			modes += "i";
		if (channel->getK())
			modes += "k";
		if (channel->getL())
			modes += "l";
		if (modes.size() == 1)
			modes.erase(0);
		response = RPL_CHANNELMODEIS(nameChannel, modes);
		send(client->getFd(), response.c_str(), response.size(), 0);
		return;
	}

	std::map<Channel*, bool>			chans = client->getChannels();

	std::map<Channel*, bool>::iterator	it = chans.find(channel);

	if (it == chans.end()) {
		std::string	response = "Couldn't find the channel in the ones where the client is.\r\n";
		send(client->getFd(), response.c_str(), response.size(), 0);
		return;
	}

	if (it->second == false) { // the user is not channel operator
		std::string	response = ERR_CHANOPRIVSNEEDED(client->getNick(), nameChannel);
		send(client->getFd(), response.c_str(), response.size(), 0);
		return;
	}

	if (!msg->params[1].compare("+i") || !msg->params[1].compare("-i"))
		handleInvit(server, msg, client, channel);
	else if (!msg->params[1].compare("+t"))
		handleTopic(server, msg, client, channel);
	else if (!msg->params[1].compare("+k") || !msg->params[1].compare("-k"))
		handleKey(server, msg, client, channel);
	else if (!msg->params[1].compare("+o") || !msg->params[1].compare("-o"))
		handleChanOp(server, msg, client, channel);
	else if (!msg->params[1].compare("+l") || !msg->params[1].compare("-l"))
		handleLimit(server, msg, client, channel);
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
