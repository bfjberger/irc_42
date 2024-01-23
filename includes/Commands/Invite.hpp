/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Invite.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorin <kmorin@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:29:51 by kmorin            #+#    #+#             */
/*   Updated: 2024/01/23 10:40:10 by kmorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INVITE_HPP
#define INVITE_HPP

#include "ACommand.hpp"

class Invite : public ACommand {

	public:
		Invite(void);
		~Invite(void);

		virtual void	execute(t_Message msg, Client client);
};

#endif
