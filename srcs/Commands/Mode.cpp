/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorin <kmorin@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:36:02 by kmorin            #+#    #+#             */
/*   Updated: 2024/02/08 13:15:36 by kmorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Commands/Mode.hpp"

Mode::Mode(void) {}

Mode::~Mode(void) {}

/**
 * https://datatracker.ietf.org/doc/html/rfc2812#section-3.1.5 USER MODE
 * https://datatracker.ietf.org/doc/html/rfc2812#section-3.2.3 CHANNEL MODE
 *
 * Parameters CHANNEL mode:
 * 		<channel> {[+|-]|i|t|k|o|l} [<topic>] [<key>] [<user>] [<limit>]
 *
 *  Parameters USER mode:
 * 		<nickname> {[+|-]|o}
 *
 * If the number of parameters is not valid, ERR_NEEDMOREPARAMS
 * If the first char of the first parameter is a '#' it's a channel
 * 	If the channel does not exist, ERR_NOSUCHCHANNEL
 * 	If the channel name is the only parameter, send the RPL_CHANNELMODEIS to the client
 * 	If the user is not a member of the channel, ERR_USERNOTINCHANNEL
 * 	If the user is not a chanop of the channel, ERR_CHANOPRIVSNEEDED
 * 	If the mode is 'i' -> handleInvit()
 * 	If the mode is 't' -> handleTopic()
 *	If the mode is 'k' -> handleKey()
 * 	If the mode is 'o' -> handleChanOp()
 * 	If the mode is 'l' -> handleLimit()
 * 		each handle function does additional test, send ERR or the appropriate RPL
 * 	If the mode is unknown, ERR_UNKNOWNMODE
 *
 * Else it's a user
 * 	If the nickname passed is not the one of the client requesting the change, ERR_USERSDONTMATCH
 * 	If the nickname is the only parameter, send the RPL_UMODEIS to the client
 * 	If the mode is '+o' or '+i' we ignore it
 * 	If the mode is '-o' we demote the client from operator to normal client and send him a custom message
 * 	If the mode is unknown, ERR_UMODEUNKNOWNFLAG
 *
 *
 * @param server The server object.
 * @param msg The message object containing the command and parameters.
 * @param client The client object.
*/

void	Mode::handleInvit(Server* server, t_Message* msg, Client* client, Channel* channel) {

	(void) server;

	if (!msg->params[1].compare("+i")) {
		channel->setI(true);
		// std::string	response = "The channel " + channel->getName() + " is now in invite-only mode.\r\n";
		std::string response = ":" + client->getNick() + " MODE " + channel->getName() + " +i\r\n";
		client->sendMessage(response);
	}
	else {
		channel->setI(false);
		std::string response = ":" + client->getNick() + " MODE " + channel->getName() + " -i\r\n";
		// std::string	response = "The channel " + channel->getName() + " is no longer in invite-only mode.\r\n";
		client->sendMessage(response);
	}
}

void	Mode::handleTopic(Server* server, t_Message* msg, Client* client, Channel* channel) {

	(void) server;

	if (!msg->params[1].compare("+t")) {
		channel->setT(true);
		std::string response = ":" + client->getNick() + " MODE " + channel->getName() + " +t\r\n";
		client->sendMessage(response);
	}
	else {
		channel->setT(false);
		std::string response = ":" + client->getNick() + " MODE " + channel->getName() + " -t\r\n";
		client->sendMessage(response);
	}
}

void	Mode::handleKey(Server* server, t_Message* msg, Client* client, Channel* channel) {

	(void) server;

	if (!msg->params[1].compare("+k") && channel->getPassword().empty()) { //set the key and the key is not yet set
		channel->setK(true);
		channel->setPassword(msg->params[2]);
		std::string response = ":" + client->getNick() + " MODE " + channel->getName() + " +k " + msg->params[2] + "\r\n";
		client->sendMessage(response);
	}
	else if (!msg->params[1].compare("+k") && !channel->getPassword().empty()) { //set the key and the key is already set
		std::string	response = ERR_KEYSET(client->getAddress(), client->getNick(), channel->getName());
		client->sendMessage(response);
	}
	else { //remove the key
		channel->setK(false);
		std::string response = ":" + client->getNick() + " MODE " + channel->getName() + " -k " + channel->getPassword() + "\r\n";
		channel->setPassword("");
		client->sendMessage(response);
	}
}

void	Mode::handleChanOp(Server* server, t_Message* msg, Client* client, Channel* channel) {

	(void) server;

	if (msg->params.size() <= 2) {
		std::string	response = ERR_NEEDMOREPARAMS(client->getAddress(), client->getNick(), msg->command);
		client->sendMessage(response);
		return;
	}

	Client*	clientChanging = channel->getClient(msg->params[2]);
	if (!clientChanging) {
		std::string	response = ERR_USERSDONTMATCH(client->getAddress(), client->getNick());
		client->sendMessage(response);
		return;
	}

	if (!msg->params[1].compare("+o")) {
		clientChanging->changeOpStatus(channel, true, client);
		std::string response = ":" + client->getNick() + " MODE " + channel->getName() + " +o " + msg->params[2] + "\r\n";
		client->sendMessage(response);
	}
	else {
		clientChanging->changeOpStatus(channel, false, client);
		std::string response = ":" + client->getNick() + " MODE " + channel->getName() + " -o" + msg->params[2] + "\r\n";
		client->sendMessage(response);
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
			if (!tmp.fail()) {
				channel->setUserLimit(limit);
				std::string response = ":" + client->getNick() + " MODE " + channel->getName() + " +l " + msg->params[2] + "\r\n";
				client->sendMessage(response);
			}
		}
		else {
			std::string	response = ERR_NEEDMOREPARAMS(client->getAddress(), client->getNick(), msg->command + msg->params[2]);
			client->sendMessage(response);
		}
	}
	else {
		channel->setL(false);
		channel->setUserLimit(-1);
		std::string response = ":" + client->getNick() + " MODE " + channel->getName() + " -l\r\n";
		client->sendMessage(response);
	}
}

void	Mode::channelMode(Server* server, t_Message* msg, Client* client) {

	std::string	nameChannel = msg->params[0];

	Channel*	channel = server->getChannel(nameChannel);

	std::string	response;

	// Check if the channel exists
	if (!channel) {
		response = ERR_NOSUCHCHANNEL(client->getAddress(), client->getNick(), nameChannel);
		client->sendMessage(response);
		return;
	}

	// print info (no need for privileges so done before those checks)
	if (msg->params.size() == 1) {
		std::string	modes = "+";
		if (channel->getI())
			modes += "i";
		if (channel->getK())
			modes += "k";
		if (channel->getT())
			modes += "t";
		if (channel->getL()) {
			modes += "l ";
			std::stringstream	ss;
			ss << channel->getUserLimit();
			modes += ss.str();
		}
		response = RPL_CHANNELMODEIS(client->getAddress(), client->getNick(), nameChannel, modes);
		client->sendMessage(response);
		return;
	}

	std::map<Channel*, bool>::iterator	it = client->getChannel(channel->getName());

	// Check if the user is a member of the channel
	if (it == client->getChannels().end()) {
		std::string	response = ERR_USERNOTINCHANNEL(client->getAddress(), client->getNick(), msg->params[2], channel->getName());
		client->sendMessage(response);
		return;
	}

	// Check if the user is a chanop of the channel
	if (it->second == false) {
		response = ERR_CHANOPRIVSNEEDED(client->getAddress(), client->getNick(), nameChannel);
		client->sendMessage(response);
		return;
	}

	if (!msg->params[1].compare("+i") || !msg->params[1].compare("-i"))
		handleInvit(server, msg, client, channel);
	else if (!msg->params[1].compare("+t") || !msg->params[1].compare("-t"))
		handleTopic(server, msg, client, channel);
	else if (!msg->params[1].compare("+k") || !msg->params[1].compare("-k"))
		handleKey(server, msg, client, channel);
	else if (!msg->params[1].compare("+o") || !msg->params[1].compare("-o"))
		handleChanOp(server, msg, client, channel);
	else if (!msg->params[1].compare("+l") || !msg->params[1].compare("-l"))
		handleLimit(server, msg, client, channel);
	else { // unknown mode
		response = ERR_UNKNOWNMODE(client->getAddress(), client->getNick(), msg->params[1]);
		client->sendMessage(response);
	}
}

void	Mode::userMode(Server* server, t_Message* msg, Client* client) {

	Client*	clientChanging = server->getClient(msg->params[0]);
	std::string	response;

	// Check if the nickname correspond to the sender
	if (clientChanging->getNick() != client->getNick()) {
		response = ERR_USERSDONTMATCH(client->getAddress(), client->getNick());
		client->sendMessage(response);
	}
	else if (msg->params.size() == 1) { // print info
		if (client->isOperator())
			response = RPL_UMODEIS(client->getAddress(), client->getNick(), "+o");
		else
			response = RPL_UMODEIS(client->getAddress(), client->getNick(), "");
		client->sendMessage(response);
	}
	else if (!msg->params[1].compare("+o")) {
		response = "You can't promote yourself to Operator this way.\r\n";
		client->sendMessage(response);
	}
	else if (!msg->params[1].compare("+i")) {
		//ignore
	}
	else if (!msg->params[1].compare("-o")) { // demote an operator
		if (client->isOperator()) {
			client->setOperator(false);
			response = "You're now no longer an operator !\r\n";
		}
		else
			response = "lol from the start you're not an operator !\r\n";
		client->sendMessage(response);
	}
	else { // unknown mode
		response = ERR_UMODEUNKNOWNFLAG(client->getAddress(), client->getNick());
		client->sendMessage(response);
	}
}

void	Mode::execute(Server* server, t_Message* msg, Client* client) {

	// Check if there is enough parameters
	if (msg->params.size() < 1) {
		std::string	response = ERR_NEEDMOREPARAMS(client->getAddress(), client->getNick(), msg->command);
		client->sendMessage(response);
		return;
	}

	if (msg->params[0][0] == '#')
		channelMode(server, msg, client);
	else
		userMode(server, msg, client);
}
