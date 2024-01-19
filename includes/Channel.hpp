/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorin <kmorin@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 13:57:03 by kmorin            #+#    #+#             */
/*   Updated: 2024/01/19 14:11:34 by kmorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include "Server.hpp"

class Channel {

	private:
		std::string	_name;
		std::string	_topic;
		std::string	_password;

		int		userLimit;

		bool	i;
		bool	t;
		bool	k;
		bool	o;
		bool	l;

	public:
		Channel(const std::string& name);
		~Channel(void);

		//Getters
		std::string	getName(void) const;
		std::string	getTopic(void) const;
		std::string	getPassword(void) const;

		//Setters
		void			setName(std::string& name);
		void			setTopic(std::string& topic);
		void			setPassword(std::string& password);

};

#endif //CHANNEL_HPP
