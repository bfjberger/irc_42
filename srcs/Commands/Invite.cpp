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

// - Paramètres:
//     - `<nickname> <channel>`
// - utiliser pour inviter un user, identifié par `<nickname>`, sur un channel, identifié par `<channel>`
// - il n’y a pas de conditions sur l’existence ou la validité du channel où l’on invite ce user
// - pour inviter un user sur un channel en invite only, le client envoyant cette commande doit être un channel operator sur ce channel
// - Numeric Replies:
//     - `ERR_NEEDMOREPARAMS`
//     - `ERR_NOSUCHNICK`
//     - `ERR_NOTONCHANNEL`
//     - `ERR_USERONCHANNEL`
//     - `ERR_CHANOPRIVSNEEDED`
//     - `RPL_INVITING`
//     - `RPL_AWAY`
