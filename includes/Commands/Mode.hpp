/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorin <kmorin@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:32:26 by kmorin            #+#    #+#             */
/*   Updated: 2024/01/23 14:30:53 by kmorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef MODE_HPP
#define MODE_HPP

#include "ACommand.hpp"

class Mode : public ACommand {

	public:
		Mode(void);
		~Mode(void);

		virtual void	execute(t_Message* msg, Client* client);
};

#endif
