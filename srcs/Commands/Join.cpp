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

void	Join::execute(Server* server, t_Message* msg, Client* client) {

	(void) server;
	(void) msg;
	(void) client;
	std::cout << "join" << std::endl;
}
