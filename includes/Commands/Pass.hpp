/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pass.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorin <kmorin@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:32:38 by kmorin            #+#    #+#             */
/*   Updated: 2024/01/24 15:12:31 by kmorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef PASS_HPP
#define PASS_HPP

#include "ACommand.hpp"

class Pass : public ACommand {

	public:
		Pass(void);
		~Pass(void);

		virtual void	execute(Server* server, t_Message* msg, Client* client);
};

#endif //PASS_HPP
