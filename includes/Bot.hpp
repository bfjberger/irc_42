/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorin <kmorin@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 16:28:47 by kmorin            #+#    #+#             */
/*   Updated: 2024/02/01 11:50:44 by kmorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOT_HPP
#define BOT_HPP

#include "Server.hpp"

class Channel;

class Server;

class Bot {

private:
		int 				_fd;

		const std::string	_name;

		struct sockaddr_in					_botAddress;

	public:
		Bot(int fd);
		~Bot();

		// Getters
		int					getFd() const;
		const std::string&	getName() const;
		const struct sockaddr_in&	getBotAddress() const;

		// Methods functions
		void	handleBot(Server* server, t_Message* msg, Client* client);

};

#endif //BOT_HPP
