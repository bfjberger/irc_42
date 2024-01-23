/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorin <kmorin@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:36:07 by kmorin            #+#    #+#             */
/*   Updated: 2024/01/23 14:35:50 by kmorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Commands/Pass.hpp"

Pass::Pass(void) {}

Pass::~Pass(void) {}

void	Pass::execute(t_Message* msg, Client* client) {

	(void) msg;
	(void) client;
	std::cout << "pass" << std::endl;
}
