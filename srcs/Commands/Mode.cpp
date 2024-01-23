/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorin <kmorin@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:36:02 by kmorin            #+#    #+#             */
/*   Updated: 2024/01/23 14:35:26 by kmorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Commands/Mode.hpp"

Mode::Mode(void) {}

Mode::~Mode(void) {}

void	Mode::execute(t_Message* msg, Client* client) {

	(void) msg;
	(void) client;
	std::cout << "mode" << std::endl;
}
