/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorin <kmorin@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:36:03 by kmorin            #+#    #+#             */
/*   Updated: 2024/01/23 14:35:31 by kmorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Commands/Nick.hpp"

Nick::Nick(void) {}

Nick::~Nick(void) {}

void	Nick::execute(t_Message* msg, Client* client) {

	(void) msg;
	(void) client;
	std::cout << "nick" << std::endl;
}
