/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorin <kmorin@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:32:39 by kmorin            #+#    #+#             */
/*   Updated: 2024/01/24 15:12:35 by kmorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef PART_HPP
#define PART_HPP

#include "ACommand.hpp"

class Part : public ACommand {

	public:
		Part(void);
		~Part(void);

		virtual void	execute(Server* server, t_Message* msg, Client* client);
};

#endif //PART_HPP
