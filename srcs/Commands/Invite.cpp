/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorin <kmorin@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:35:58 by kmorin            #+#    #+#             */
/*   Updated: 2024/01/24 14:23:31 by kmorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Commands/Invite.hpp"

Invite::Invite(void) {}

Invite::~Invite(void) {}

void	Invite::execute(Server* server, t_Message* msg, Client* client) {

	(void) server;
	(void) client;
	(void) msg;
	std::cout << "invite" << std::endl;
}
