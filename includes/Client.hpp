/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorin <kmorin@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 17:03:23 by pvong             #+#    #+#             */
/*   Updated: 2024/01/30 17:18:10 by kmorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

#include "Server.hpp"

class Channel;

class Server;

class Client {

	private:
		int 		_fd;

		bool		_receivedInfo;
		bool		_isLogged;
		bool		_welcomeSent;
		bool		_isRegistered;
		bool		_isInChannel;
		bool		_isOperator;
		bool		_deconnection;

		std::string	_password;
		std::string	_nick;
		std::string	_userName;
		std::string	_hostname;
		std::string _currentChannel;

		std::map<Channel*, bool>	_channels;

		int	_maxChannels;

	public:
		Client(int fd);
		Client();
		~Client();

		// Getters
		int					getFd() const;
		bool				hasReceivedInfo() const;
		bool				isLogged() const;
		bool				welcomeSent() const;
		bool				isRegistered() const;
		bool				isInChannel() const;
		bool				isOperator() const;
		bool				getDeconnection() const;
		const std::string&	getNick() const;
		const std::string&	getUserName() const;
		const std::string&	getPass() const;
		const std::string&	getHostname() const;
		const std::string&	getCurrentChannel() const;
		const std::map<Channel*, bool>&	getChannels() const;
		const int&		getMaxChannels() const;
		static Client*				getClientByFd(Server* server, int clientFd);

		// Setters
		void	setLogged(bool isLogged);
		void	setReceivedInfo(bool receivedInfo);
		void	setWelcomeSent(bool welcomeSent);
		void	setRegistered(bool isRegistered);
		void	setInChannel(bool inChannel);
		void	setOperator(bool isOperator);
		void	setNick(std::string nick);
		void	setUserName(std::string userName);
		void	setPass(std::string pass);
		void	setHostname(std::string hostname);
		void	setCurrentChannel(std::string channel);
		void	setDeconnection(bool deconnection);

		// Clients Methods
		void	sendMessage(std::string& message);

		void	addChannel(Channel* chan, bool chanOp);
		void	removeChannel(Channel* chan);
		void	changeOpStatus(Channel* chan, bool chanOp, Client* client);

		// TODO: Not Implemented yet
		void	logIn();

		// Helpers function
		void	printInfo() const;
};

#endif // CLIENT_HPP
