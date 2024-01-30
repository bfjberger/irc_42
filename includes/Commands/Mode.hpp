/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorin <kmorin@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:32:26 by kmorin            #+#    #+#             */
/*   Updated: 2024/01/30 08:50:52 by kmorin           ###   ########.fr       */
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

		void			handleInvit(Server* server, t_Message* msg, Client* client, Channel* channel);
		void			handleTopic(Server* server, t_Message* msg, Client* client, Channel* channel);
		void			handleKey(Server* server, t_Message* msg, Client* client, Channel* channel);
		void			handleChanOp(Server* server, t_Message* msg, Client* client, Channel* channel);
		void			handleLimit(Server* server, t_Message* msg, Client* client, Channel* channel);

		void			channelMode(Server* server, t_Message* msg, Client* client);
		void			userMode(Server* server, t_Message* msg, Client* client);
		virtual void	execute(Server* server, t_Message* msg, Client* client);
};

#endif //MODE_HPP
