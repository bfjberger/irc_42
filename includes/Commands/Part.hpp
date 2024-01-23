/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorin <kmorin@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:32:39 by kmorin            #+#    #+#             */
/*   Updated: 2024/01/23 10:47:38 by kmorin           ###   ########.fr       */
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

		virtual void	execute(t_Message msg, Client client);
};

#endif