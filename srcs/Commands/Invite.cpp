/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorin <kmorin@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:35:58 by kmorin            #+#    #+#             */
/*   Updated: 2024/01/30 10:32:52 by kmorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Commands/Invite.hpp"

Invite::Invite(void) {}

Invite::~Invite(void) {}

/**
 * ajouter un moyen de savoir si le client a ete invite dans un channel
 * et c'est ca qui devrait etre modifie dans cette commande
 * et cette valeur sera checker dans le join
*/

void	Invite::execute(Server* server, t_Message* msg, Client* client) {

	(void) server;
	(void) client;
	(void) msg;
	std::cout << "invite" << std::endl;
}
