/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorin <kmorin@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:36:02 by kmorin            #+#    #+#             */
/*   Updated: 2024/01/26 16:16:00 by kmorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Commands/Mode.hpp"

Mode::Mode(void) {}

Mode::~Mode(void) {}

/**
 * https://datatracker.ietf.org/doc/html/rfc2812#section-3.1.5 User MODE
 * https://datatracker.ietf.org/doc/html/rfc2812#section-3.2.3 Channel MODE
 *
 * Parameters:
 * 		<nickname> {[+|-]|i|w|s|o}
 *
 * @param server The server object.
 * @param msg The message object containing the command and parameters.
 * @param client The client object.
*/
void	Mode::execute(Server* server, t_Message* msg, Client* client) {

	(void) server;
	(void) msg;
	(void) client;
	std::cout << "mode" << std::endl;
}
