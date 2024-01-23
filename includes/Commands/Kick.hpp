/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Kick.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorin <kmorin@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:32:15 by kmorin            #+#    #+#             */
/*   Updated: 2024/01/23 14:30:40 by kmorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef KICK_HPP
#define KICK_HPP

#include "ACommand.hpp"

class Kick : public ACommand {

	public:
		Kick(void);
		~Kick(void);

		virtual void	execute(t_Message* msg, Client* client);
};

#endif
