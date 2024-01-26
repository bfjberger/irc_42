/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorin <kmorin@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:35:59 by kmorin            #+#    #+#             */
/*   Updated: 2024/01/24 14:05:15 by kmorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Commands/Join.hpp"

Join::Join(void) {}

Join::~Join(void) {}

void Join::execute(Server* server, t_Message* msg, Client* client) {
	(void)server;
	(void)msg;
	(void)client;

	std::string channelName = msg->params[0]; // Get the channel name from the message parameters

	// Check if the channel already exists
	Channel* channel = server->getChannel(channelName);
	if (channel == NULL) {
		// Channel doesn't exist, create a new one
		channel = new Channel(channelName);
		server->addChannel(channel);
	}

	// Set the client's current channel
	client->setCurrentChannel(channel->getName());
	client->setInChannel(true);

	// Add the client to the channel
	channel->addClient(client);

	// Send a response to the client
	std::string response = "You have joined channel " + channelName + "\r\n";
	send(client->getFd(), response.c_str(), response.length(), 0);
	client->printInfo();
}
