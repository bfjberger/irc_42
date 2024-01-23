/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Kill.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorin <kmorin@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:36:01 by kmorin            #+#    #+#             */
/*   Updated: 2024/01/23 14:35:21 by kmorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Commands/Kill.hpp"

Kill::Kill(void) {}

Kill::~Kill(void) {}

void	Kill::execute(t_Message* msg, Client* client) {

	(void) msg;
	(void) client;
	std::cout << "kill" << std::endl;
}
