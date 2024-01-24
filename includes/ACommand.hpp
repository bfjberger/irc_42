/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ACommand.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorin <kmorin@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:18:23 by kmorin            #+#    #+#             */
/*   Updated: 2024/01/24 11:43:54 by kmorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ACOMMAND_HPP
#define ACOMMAND_HPP

// #include "Server.hpp"
#include <iostream>

class Server;
class Client;
typedef struct s_Message t_Message;

class ACommand {

	public:
		ACommand(void);
		virtual ~ACommand(void);

		virtual void	execute(t_Message* msg, Client* client) = 0;
};

#endif //ACOMMAND_HPP
