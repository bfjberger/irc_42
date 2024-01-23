/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorin <kmorin@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:32:33 by kmorin            #+#    #+#             */
/*   Updated: 2024/01/23 15:37:14 by kmorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef USER_HPP
#define USER_HPP

#include "ACommand.hpp"

class User : public ACommand {

	public:
		User(void);
		~User(void);

		virtual void	execute(t_Message* msg, Client* client);
};

#endif
