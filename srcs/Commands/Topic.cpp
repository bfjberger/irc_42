/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorin <kmorin@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:36:11 by kmorin            #+#    #+#             */
/*   Updated: 2024/01/23 14:36:13 by kmorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Commands/Topic.hpp"

Topic::Topic(void) {}

Topic::~Topic(void) {}

void	Topic::execute(t_Message* msg, Client* client) {

	(void) msg;
	(void) client;
	std::cout << "topic" << std::endl;
}
