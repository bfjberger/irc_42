/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorin <kmorin@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 13:57:03 by kmorin            #+#    #+#             */
/*   Updated: 2024/02/05 15:57:01 by kmorin           ###   ########.fr       */
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
		// vector de strings pour checker la liste des clients qui ont ete invite a joindre un channel
		std::vector<std::string> invitedClientVector;

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
		bool getInvitedClientVector(std::string ClientInvited) const;
		bool	isClientInChannel(std::string clientName) const;

		int	getUserLimit() const;
		bool	getI() const;
		bool	getK() const;
		bool	getL() const;
		bool	getT() const;

		const std::map<std::string, Client*>&	getClients() const;
		Client*									getClient(std::string clientName);

		//Setters
		void	setName(std::string name);
		void	setTopic(std::string topic);
		void	setPassword(std::string password);
		void 	setInvitedClientVector(std::string ClientInvited);

		void	setUserLimit(int i);
		void	setI(bool status);
		void	setK(bool status);
		void	setL(bool status);
		void	setT(bool status);

		//Channel Methods
		void			addClient(Client* client);
		void			removeClient(Client* client);
		void			sendMessageToAllClients(std::string& message, int flag = 0);
		void			sendToAllButOne(std::string& message, Client* client, int flag = 0);
		void			deleteInvitedClient(std::string invitedClient);


};

#include "Client.hpp"
#include "Server.hpp"

#endif //CHANNEL_HPP
