/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ACommand.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorin <kmorin@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:18:23 by kmorin            #+#    #+#             */
/*   Updated: 2024/01/23 10:56:41 by kmorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ACOMMAND_HPP
#define ACOMMAND_HPP

#include "Server.hpp"

class Client;
// struct t_Message;

class ACommand {

	private:

	public:
		ACommand(void);
		virtual ~ACommand(void);

		virtual void	execute(t_Message msg, Client client) = 0;
};

#endif
