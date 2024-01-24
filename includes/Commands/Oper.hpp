/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Oper.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorin <kmorin@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:32:40 by kmorin            #+#    #+#             */
/*   Updated: 2024/01/24 15:12:35 by kmorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef OPER_HPP
#define OPER_HPP

#include "ACommand.hpp"

class Oper : public ACommand {

	public:
		Oper(void);
		~Oper(void);

		virtual void	execute(Server* server, t_Message* msg, Client* client);
};

#endif //OPER_HPP
