/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorin <kmorin@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:29:51 by kmorin            #+#    #+#             */
/*   Updated: 2024/01/23 10:47:23 by kmorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef JOIN_HPP
#define JOIN_HPP

#include "ACommand.hpp"

class Join : public ACommand {

	public:
		Join(void);
		~Join(void);

		virtual void	execute(t_Message msg, Client client);
};

#endif
