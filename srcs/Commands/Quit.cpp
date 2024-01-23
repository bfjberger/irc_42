/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorin <kmorin@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:36:10 by kmorin            #+#    #+#             */
/*   Updated: 2024/01/23 14:36:03 by kmorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Commands/Quit.hpp"

Quit::Quit(void) {}

Quit::~Quit(void) {}

void	Quit::execute(t_Message* msg, Client* client) {

	(void) msg;
	(void) client;
	std::cout << "quit" << std::endl;
}
