/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Kill.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorin <kmorin@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:32:23 by kmorin            #+#    #+#             */
/*   Updated: 2024/01/24 15:12:51 by kmorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef KILL_HPP
#define KILL_HPP

#include "ACommand.hpp"

class Kill : public ACommand {

	public:
		Kill(void);
		~Kill(void);

		virtual void	execute(Server* server, t_Message* msg, Client* client);
};

#endif //KILL_HPP
