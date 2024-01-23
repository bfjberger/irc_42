/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorin <kmorin@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:36:06 by kmorin            #+#    #+#             */
/*   Updated: 2024/01/23 14:35:44 by kmorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Commands/Part.hpp"

Part::Part(void) {}

Part::~Part(void) {}

void	Part::execute(t_Message* msg, Client* client) {

	(void) msg;
	(void) client;
	std::cout << "part" << std::endl;
}
