/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorin <kmorin@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 17:03:23 by pvong             #+#    #+#             */
/*   Updated: 2024/01/23 14:46:39 by kmorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

#include "ft_irc.hpp"

class Client {

	private:
		int 		_fd;

		bool		_receivedInfo;
		bool		_isLogged;
		bool		_welcomeSent;
		bool		_isRegistered;
		bool		_isInChannel;

		std::string	_password;
		std::string	_nick;
		std::string	_userName;
		std::string	_realName;
		std::string	_hostname;

	public:
		Client(int fd);
		Client();
		~Client();

		// Getters
		int			getFd() const;
		bool		hasReceivedInfo() const;
		bool		isLogged() const;
		bool		welcomeSent() const;
		bool		isRegistered() const;
		bool		isInChannel(void) const;
		std::string	getNick() const;
		std::string	getUserName() const;
		std::string	getRealName() const;
		std::string	getPass() const;
		std::string	getHostname() const;

		// Setters
		void	setLogged(bool isLogged);
		void	setReceivedInfo(bool receivedInfo);
		void	setWelcomeSent(bool welcomeSent);
		void	setRegistered(bool isRegistered);
		void	setInChannel(bool inChannel);
		void	setNick(std::string nick);
		void	setUserName(std::string userName);
		void	setPass(std::string pass);
		void	setRealName(std::string realName);
		void	setHostname(std::string hostname);

		// TODO: Not Implemented yet
		void	logIn();

		// Helpers function
		void	printInfo() const;
};

#endif // CLIENT_HPP
