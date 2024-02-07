/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorin <kmorin@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 13:57:03 by kmorin            #+#    #+#             */
/*   Updated: 2024/02/07 16:00:56 by kmorin           ###   ########.fr       */
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
		std::map<int, Client*>	_clients;

		std::vector<int>		_invitedClient;

		int	_userLimit;

		bool	i;
		bool	k;
		bool	l;
		bool	t;

	public:
		Channel(const std::string& name);
		~Channel(void);

		//Getters
		std::string	getName(void) const;
		std::string	getTopic(void) const;
		std::string	getPassword(void) const;
		bool		getInvitedClient(int fd) const;
		bool		isClientInChannel(int fd) const;

		int		getUserLimit() const;
		bool	getI() const;
		bool	getK() const;
		bool	getL() const;
		bool	getT() const;

		const std::map<int, Client*>&		getClients() const;
		Client*								getClient(std::string nickname);
		std::map<int, Client*>::iterator	getClientIt(std::string nickname);

		//Setters
		void	setName(std::string name);
		void	setTopic(std::string topic);
		void	setPassword(std::string password);
		void 	setInvitedClient(int fd);

		void	setUserLimit(int i);
		void	setI(bool status);
		void	setK(bool status);
		void	setL(bool status);
		void	setT(bool status);

		//Channel Methods
		void			addClient(Client* client);
		void			removeClient(Client* client);
		void			removeClientFromChannel(int fd);
		void			sendMessageToAllClients(std::string& message, int flag = 0);
		void			sendToAllButOne(std::string& message, Client* client, int flag = 0);
		void			deleteInvitedClient(int fd);
};

#include "Client.hpp"
#include "Server.hpp"

#endif //CHANNEL_HPP
