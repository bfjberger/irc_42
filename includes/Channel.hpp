/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorin <kmorin@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 13:57:03 by kmorin            #+#    #+#             */
/*   Updated: 2024/01/19 14:11:34 by kmorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include "ft_irc.hpp"

class Client;

class Channel {

	private:
		std::string	_name;
		std::string	_topic;
		std::string	_password;
		std::map<std::string, Client*>	_clients;

		int		userLimit;

		bool	i;
		bool	t;
		bool	k;
		bool	o;
		bool	l;

	public:
		Channel(const std::string& name);
		~Channel(void);

		//Getters
		std::string	getName(void) const;
		std::string	getTopic(void) const;
		std::string	getPassword(void) const;

		//Setters
		void			setName(std::string& name);
		void			setTopic(std::string& topic);
		void			setPassword(std::string& password);

		//Channel Methods
		void			addClient(Client* client);
		void			removeClient(Client* client);
		void			sendMessageToAllClients(std::string& message);
		void			sendToAllButOne(std::string& message, Client* client);

};

#include "Client.hpp"
#include "Server.hpp"

#endif //CHANNEL_HPP
