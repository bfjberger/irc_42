/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Oper.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorin <kmorin@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:36:05 by kmorin            #+#    #+#             */
/*   Updated: 2024/01/23 14:35:40 by kmorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Commands/Oper.hpp"

Oper::Oper(void) {}

Oper::~Oper(void) {}

void	Oper::execute(t_Message* msg, Client* client) {

	(void) msg;
	(void) client;
	std::cout << "oper" << std::endl;
}
