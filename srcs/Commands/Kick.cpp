/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorin <kmorin@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:36:00 by kmorin            #+#    #+#             */
/*   Updated: 2024/01/23 14:35:15 by kmorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Commands/Kick.hpp"

Kick::Kick(void) {}

Kick::~Kick(void) {}

void	Kick::execute(t_Message* msg, Client* client) {

	(void) msg;
	(void) client;
	std::cout << "kick" << std::endl;
}
