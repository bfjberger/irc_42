/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Topic.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorin <kmorin@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:32:34 by kmorin            #+#    #+#             */
/*   Updated: 2024/01/23 14:31:19 by kmorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef TOPIC_HPP
#define TOPIC_HPP

#include "ACommand.hpp"

class Topic : public ACommand {

	public:
		Topic(void);
		~Topic(void);

		virtual void	execute(t_Message* msg, Client* client);
};

#endif
