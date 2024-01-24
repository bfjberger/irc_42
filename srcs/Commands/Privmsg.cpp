/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorin <kmorin@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:36:09 by kmorin            #+#    #+#             */
/*   Updated: 2024/01/24 14:05:30 by kmorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Commands/Privmsg.hpp"

Privmsg::Privmsg(void) {}

Privmsg::~Privmsg(void) {}

void	Privmsg::execute(Server* server, t_Message* msg, Client* client) {

	(void) server;
	(void) msg;
	(void) client;
	std::cout << "privmsg" << std::endl;
}
