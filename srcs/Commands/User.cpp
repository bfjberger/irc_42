/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorin <kmorin@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:36:12 by kmorin            #+#    #+#             */
/*   Updated: 2024/01/23 14:36:18 by kmorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Commands/User.hpp"

User::User(void) {}

User::~User(void) {}

void	User::execute(t_Message* msg, Client* client) {

	(void) msg;
	(void) client;
	std::cout << "user" << std::endl;
}
