/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Privmsg.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorin <kmorin@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:32:36 by kmorin            #+#    #+#             */
/*   Updated: 2024/01/23 10:47:43 by kmorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef PRIVSMG_HPP
#define PRIVSMG_HPP

#include "ACommand.hpp"

class Privmsg : public ACommand {

	public:
		Privmsg(void);
		~Privmsg(void);

		virtual void	execute(t_Message msg, Client client);
};

#endif