/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorin <kmorin@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:29:51 by kmorin            #+#    #+#             */
/*   Updated: 2024/01/29 12:52:11 by kmorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef JOIN_HPP
#define JOIN_HPP

#include "ACommand.hpp"
#include "Channel.hpp"

class Join : public ACommand {

	public:
		Join(void);
		~Join(void);

		void			channelCreation(Server* server, t_Message* msg, Client* client, Channel* channel);
		void			joinChannelPassword(Server* server, t_Message* msg, Client* client, Channel* channel);
		void			joinChannel(Server* server, t_Message* msg, Client* client, Channel* channel);

		virtual void	execute(Server* server, t_Message* msg, Client* client);
};

#endif //JOIN_HPP
