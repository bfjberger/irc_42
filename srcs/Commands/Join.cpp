/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorin <kmorin@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:35:59 by kmorin            #+#    #+#             */
/*   Updated: 2024/01/23 14:35:10 by kmorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Commands/Join.hpp"

Join::Join(void) {}

Join::~Join(void) {}

void	Join::execute(t_Message* msg, Client* client) {

	(void) msg;
	(void) client;
	std::cout << "join" << std::endl;
}
