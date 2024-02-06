/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorin <kmorin@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:36:09 by kmorin            #+#    #+#             */
/*   Updated: 2024/02/06 10:37:13 by kmorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Commands/Privmsg.hpp"

Privmsg::Privmsg(void) {}

Privmsg::~Privmsg(void) {}

/**
 * If the input is /DCC SEND targetUserName filePath
 * It will automatically expand to
 *		PRIVMSG targetUserName :DCC SEND filePath sender'sIPAddress sender'sPort nbOfBytes
 *
 * * Example:
 * PRIVMSG test :DCC SEND dalnet.txt 2130706433 50411 3357
 * @param server
 * @param msg
 * @param client
 */
void	Privmsg::dcchandler(Server* server, t_Message* msg, Client* client) {

	Client*	target = server->getClient(msg->params[0]);

	std::string	dccContent;
	dccContent = getParams(msg, 1);

	std::string	rpl(msg->command);
	rpl = ":" + client->getNick() + " " + rpl + " ";
	rpl += client->getNick() + " " + dccContent + "\r\n";
	// std::cout << "resultat: " << rpl << std::endl;
	target->sendMessage(rpl);
}

/**
 * https://datatracker.ietf.org/doc/html/rfc2812#section-3.3.1
 *
 * Parameters:
 * 		<target> <text>
 *
 * The target of the message can be a channel or a client
 *
 * Get the message to be sent, add the closing caracters and erase the ':' at the start if present
 * If the target of the message is the bot and with at least one parameter -> handleBot()
 * If the number of parameters is not valid, ERR_NEEDMOREPARAMS
 * If the target of the message is a channel, send it to all clients on the channel
 * 		If the client is not part of the channel, ERR_NOTONCHANNEL
 * 		If the channel does not exist, ERR_NOSUCHCHANNEL
 * If the target of the message is a client, send the message to him
 *		irssi expand the DCC SEND so check if it's the case -> dcchandler()
 * 		If the client does not exist, ERR_NOSUCHNICK
 * 		Else send the RPL_PRIVMSG to the client
 * If the target is not a channel nor a client, ERR_NOSUCHNICK
 *
 * @param server The server instance.
 * @param msg The message containing the command and parameters.
 * @param client The client who sent the command.
 */
void	Privmsg::execute(Server* server, t_Message* msg, Client* client) {

	std::string	response;

	// rplMsg is the message to send to the channel or the client
	std::string rplMsg = getParams(msg, 1) + "\r\n";
	if (rplMsg[0] == ':') {
		rplMsg.erase(0, 1);
	}

	if (msg->params.size() >= 1 && msg->params[0] == server->getBot()->getName()) {
		server->getBot()->handleBot(server, msg, client);
		return;
	}

	// Check if there is enough parameters
	if (msg->params.size() < 2) {
		response = ERR_NEEDMOREPARAMS(client->getAddress(), client->getNick(), msg->command);
		client->sendMessage(response);
		return;
	}

	// if the first param is a channel
	// send the message to all the clients in the channel
	if (server->isChannel(msg->params[0]) == true) {
		Channel* channel = server->getChannel(msg->params[0]);
		// If the client is not in the channel send an error message
		if (channel != NULL && channel->isClientInChannel(client->getNick()) == false) {
			response = ERR_NOTONCHANNEL(client->getAddress(), client->getNick(), msg->params[0]);
			client->sendMessage(response);
			return;
		}
		// If the client is in the channel send the message to all the clients in the channel
		else if (channel != NULL) {
			std::string clientNick = client->getNick();
			response = ":" + clientNick + "!" + client->getUserName() + "@" + client->getHostname() + " PRIVMSG " + msg->params[0];
			response += " " + rplMsg + "\r\n";
			channel->sendToAllButOne(response, client);
		}
		// If the channel does not exist send an error message
		else {
			response = ERR_NOSUCHCHANNEL(client->getAddress(), client->getNick(), msg->params[0]);
			client->sendMessage(response);
		}
	}

	// if the first param is a client
	// send the message to the client
	else if (server->isNick(msg->params[0]) == true) {
		Client* target = server->getClient(msg->params[0]);
		if (target != NULL) {
			if (msg->params[1].compare(":DCC")) { // Go to dcchandler for handling the format for the file transfer
				dcchandler(server, msg, client);
				return;
			}
			else {
				response = RPL_PRIVMSG(client->getAddress(), client->getNick(), rplMsg);
				std::cout << COLOR("[" << client->getNick() << "] -> [" << target->getNick() << "] : " << rplMsg, GREEN) << std::endl;
				target->sendMessage(response);
			}
		}
		else { // The target does not exist on the server
			response = ERR_NOSUCHNICK(client->getAddress(), client->getNick(), msg->params[0]);
			client->sendMessage(response);
		}
	}
	else { // Not a client nor a channel
		response = ERR_NOSUCHNICK(client->getAddress(), client->getNick(), msg->params[0]);
		client->sendMessage(response);
	}
}
