/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nick.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorin <kmorin@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:32:41 by kmorin            #+#    #+#             */
/*   Updated: 2024/01/23 10:47:34 by kmorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef NICK_HPP
#define NICK_HPP

#include "ACommand.hpp"

class Nick : public ACommand {

	public:
		Nick(void);
		~Nick(void);

		virtual void	execute(t_Message msg, Client client);
};

#endif